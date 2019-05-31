import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

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


@app.route("/")
@login_required
def index():

    # Get all information about user's purchases and holdings
    pur_tab = db.execute("SELECT symbol, SUM(share) FROM purchases JOIN users ON purchases.id = users.id WHERE users.id = :id GROUP BY symbol HAVING SUM(share) > 0", id = session["user_id"])
    user_val = db.execute("SELECT cash, username FROM users WHERE id = :id", id = session["user_id"])

    # lookup current prices of all shares owned and calculate user's total worth
    total = 0
    for row in pur_tab:
        quote = lookup(row["symbol"])
        row["price"] = usd(quote["price"])
        row["hold_val"] = quote["price"] * row["SUM(share)"]
        total += float(row["hold_val"])
        row["hold_val"] = usd(row["hold_val"])

    user_val[0]["total"] = usd(float(total) + float(user_val[0]["cash"]))
    user_val[0]["cash"] = usd(user_val[0]["cash"])

    return render_template("index.html", pur_tab=pur_tab, user_val=user_val)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check if users requested for a valid amount of shares
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not shares.isdigit():
            return apology("The indicated shares must be a positive integer")

        # Check if symbol is valid and look up price
        quote = lookup(symbol)
        if quote == None:
            return apology("Invalid symbol")

        # Check if user's amount of cash left is enough for purchase
        else:
            cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
            purchase_price = int(shares) * float(quote["price"])
            cur_cash = float(cash[0]["cash"])

            if cur_cash < purchase_price:
                return apology("Not enough cash for current purchase")

            # Finish transaction and redirect to index
            else:
                db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash = float(cur_cash - purchase_price), id = session["user_id"])
                db.execute("INSERT INTO purchases (id, symbol, share, unit_purchase_price) VALUES (:id, :symbol, :share, :unit_price)",
                id = session["user_id"], symbol = quote["symbol"], share = int(shares), unit_price = quote["price"])
                return redirect("/")


    # User reached route via GET
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():

    username = request.args.get("username")
    if len(username) > 0 and len(db.execute("SELECT username FROM users WHERE username = :username", username = username)) == 0:
        return jsonify(True)
    else:
        return jsonify(False)




@app.route("/history")
@login_required
def history():

    # Get all information about user's purchases and sales
    table = db.execute("SELECT symbol, share, datetime, unit_purchase_price FROM purchases WHERE id = :id ORDER BY datetime DESC", id = session["user_id"])

    return render_template("history.html", table = table)


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
    # User reach route via POST (by submitting a form via POST)
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("No listings found")

        else:
            return render_template("quoted.html", name=quote["name"], price=usd(float(quote["price"])), symbol=quote["symbol"])

    # User reach route via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        uname = request.form.get("username")
        pw = generate_password_hash(request.form.get("password"))
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Ensure password is entered correctly twice
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match")

        else:
            result = db.execute("INSERT INTO users(username, hash) VALUES (:uname, :pw)", uname = uname, pw = pw)

            if not result:
                return apology("The username is already taken")

        # Redirect user to login page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get info about stocks and user's shares
        selling = request.form.get("symbol")
        selling = selling.upper()
        user_data = db.execute("SELECT symbol, SUM(share),cash FROM purchases JOIN users ON purchases.id = users.id WHERE users.id = :id AND symbol = :symbol GROUP BY symbol", id = session["user_id"], symbol = str(selling))
        quantity = int(request.form.get("shares"))
        quote = lookup(selling)
        if quote == None:
            return apology("No listings found")

        # Check if user owns stated shares and whether if he has enough quantity to sell
        if len(user_data) == 1 and int(user_data[0]["SUM(share)"]) > 0:

            if quantity > int(user_data[0]["SUM(share)"]):
                return apology("You do not own that many stocks")
            else:
                db.execute("INSERT INTO purchases(id, symbol, share, unit_purchase_price) VALUES (:id, :symbol, :share, :price)",
                id = session["user_id"], symbol = selling, share = -(quantity), price = quote["price"])
                db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash = user_data[0]["cash"] + quantity * quote["price"], id = session["user_id"])
                return redirect("/")
        else:
            return apology(f"You do not own any {selling} stocks")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        user_data = db.execute("SELECT symbol FROM purchases WHERE id = :id GROUP BY symbol", id = session["user_id"])
        return render_template("sell.html", user_data=user_data)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

@app.route("/change", methods=["GET","POST"])
@login_required
def change():

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check if users retyped their passwords correctly for caution, then check if old password is correct and if new password is not empty

        rows = db.execute("SELECT hash FROM users WHERE id = :id", id = session["user_id"])

        if request.form.get("old") != request.form.get("check_old") or request.form.get("new") != request.form.get("check_new"):
            return apology("Passwords do not match")

        elif not request.form.get("new") or not check_password_hash(rows[0]["hash"], request.form.get("old")):
            return apology("Invalid Password")

        else:
            new_pw = generate_password_hash(request.form.get("new"))
            db.execute("UPDATE users SET hash = :new_pw WHERE id = :id", new_pw = new_pw, id = session["user_id"])
            flash("Success")
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("change.html")
