import os
import hashlib
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT * FROM stocks WHERE username = :username", username=session["user_id"])
    rowss = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    rowsss = db.execute("SELECT DISTINCT(name) FROM boughtsss;")
    return render_template("index.html",rows = rows,rowss=rowss,rowsss=rowsss)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        #tanking in details for symbol typed by user
        detail = lookup(request.form.get("symbol"))
        if detail == None:
            return apology("invalid share abbreviation!!")

        #declaring variable for price
        a = detail["price"]
        company_logo = detail["symbol"]
        company_name = detail["name"]

        #tanking in details for number of stacks to be bought by user
        num = int(request.form.get("numberOfStocks"))
        if num <= 0:
            return apology("invalid share count!!")

        now = datetime.now()
        dt_string = now.strftime("%d/%m/%Y %H:%M:%S")

        #total money required for buying
        total_expenditure = a*num

        #checking balance left in account
        row = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        balance_account = row[0]["cash"]

        u =  session["user_id"]

        try:
            #if already having the type of stock
            initial_stocks = db.execute(f"SELECT totalShares FROM stocks WHERE username = '{u}' AND Symbol = '{company_logo}';")
            total_stocks = initial_stocks[0]["totalShares"]

        except:
            #if not bought that stock previously
            total_stocks = 0
            db.execute("INSERT INTO stocks(username, Symbol, totalShares) VALUES (:username, :Symbol, :totalShares)",username = session["user_id"], Symbol = company_logo, totalShares = total_stocks)

        #if user has enough money to buy
        if total_expenditure <=  balance_account:

            #new total bought stock......
            total_stocks_new = num + total_stocks

            #update his stock count
            db.execute(f"UPDATE stocks SET totalShares = '{total_stocks_new}' WHERE username = '{u}' AND Symbol = '{company_logo}';")

            #insert transaction history into system
            db.execute("INSERT INTO boughtsss(username, Symbol, Name, Shares, price , Total, TrasactioTime) VALUES (:username, :Symbol, :Name, :Shares, :price, :Total, :TrasactioTime)",username = session["user_id"], Symbol = company_logo, Name = company_name, Shares = num, price = a, Total = total_expenditure, TrasactioTime = dt_string)

            #update his account balance
            remaining_cash = balance_account - total_expenditure
            db.execute(f"UPDATE users SET cash = '{remaining_cash}' WHERE id = '{u}';")

            return redirect("/")

        return apology("not enough money")
    return apology("TODO")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM boughtsss WHERE username = :username", username=session["user_id"])
    rowss = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    return render_template("history.html",rows = rows,rowss=rowss)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        t = lookup(request.form.get("symbol"))

        if t == None:
            return apology("no match")
        else:
            return render_template("quoted.html", quote=t)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get("name")
        key = request.form.get("password")
        key_verify = request.form.get("ConfirmPassword")

        if not name:
            return apology("type username bruh")

        if not key:
            return apology("type password bruh")

        if key != key_verify:
            return apology("password not matching....bruh")

        else:
            #hashing password for security reasons........
            hash = generate_password_hash(key)

            #passing registered username and password to database
            db.execute("INSERT INTO users(username,hash) VALUES (:username, :hash)", username = name, hash = hash)
            return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    u =  session["user_id"]

    if request.method == "GET":
        return render_template("sell.html")
    else:
        #tanking in details for number of stacks to be bought by user
        num = int(request.form.get("numberOfStocks"))
        if num <= 0:
            return apology("invalid share count!!")

        #tanking in details for symbol typed by user
        stock_sell_name = request.form.get("symbol")

        #checking stocks left in account
        total_stock_having = db.execute(f"SELECT totalShares FROM stocks WHERE Symbol = '{stock_sell_name}' AND username = '{u}';")
        total_stock_number = total_stock_having[0]["totalShares"]

        if total_stock_number >= num:
            detail = lookup(request.form.get("symbol"))
            if detail == None:
                return apology("invalid share abbreviation!!")

            #declaring variable for price
            a = detail["price"]
            company_logo = detail["symbol"]
            company_name = detail["name"]

            now = datetime.now()
            dt_string = now.strftime("%d/%m/%Y %H:%M:%S")

            #total money required for buying
            total_profit = a*num


            row = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
            balance_account = row[0]["cash"]

            try:
                #if already having the type of stock
                initial_stocks = db.execute(f"SELECT totalShares FROM stocks WHERE username = '{u}';")
                total_stocks_initial = initial_stocks[0]["totalShares"]

            except:
                #if not bought that stock previously
                db.execute("INSERT INTO stocks(username, Symbol, totalShares) VALUES (:username, :Symbol, :totalShares)",username = session["user_id"], Symbol = company_logo, totalShares = 0)
                total_stocks_initial = 0

            #new total bought stock......
            total_stocks = total_stocks_initial - num

            #update his stock count
            db.execute(f"UPDATE stocks SET totalShares = '{total_stocks}' WHERE username = '{u}' AND Symbol = '{company_logo}';")

            #insert transaction history into system
            db.execute("INSERT INTO boughtsss(username, Symbol, Name, Shares, price , Total, TrasactioTime) VALUES (:username, :Symbol, :Name, :Shares, :price, :Total, :TrasactioTime)",username = session["user_id"], Symbol = company_logo, Name = company_name, Shares = (-num), price = a, Total = total_profit, TrasactioTime = dt_string)

            #update his account balance
            remaining_cash = balance_account + total_profit
            db.execute(f"UPDATE users SET cash = '{remaining_cash}' WHERE id = '{u}';")

            return redirect("/")

        else:
            return apology("not enough stocks")

@app.route("/changepass", methods=["GET", "POST"])
@login_required
def change():
    """change your pass"""
    u =  session["user_id"]
    if request.method == "GET":
        return render_template("changepassword.html")
    else:
        newpass = request.form.get("newpass")
        hashey_new = generate_password_hash(newpass)
        db.execute(f"UPDATE users SET hash = '{hashey_new}' WHERE id = '{u}';")
        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
