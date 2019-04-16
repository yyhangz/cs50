import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():

    # Check if any sections are unfilled
    if not request.form.get("FavArt"):
        return render_template("error.html", message="Missing section \"Favourite Artist/Band\"")
    elif request.form.get("FavIns") == "Favourite type of instrument":
        return render_template("error.html", message="Missing section \"Favourite tyoe of instrument\"")

    # If successful, write in csv file
    file = open("survey.csv", "a")
    writer = csv.writer(file)
    writer.writerow((request.form.get("FavArt"), request.form.get("VocOrIns"), request.form.get("FavIns")))
    file.close()
    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():

    # Read csv file to create table
    file = open("survey.csv", "r")
    reader = csv.reader(file)
    data = list(reader)
    return render_template("sheet.html", data=data)
