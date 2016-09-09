from flask import Flask
from _primality import *
app = Flask(__name__)

@app.route("/")
def hello():
    return "Hellow World!"

if  __name__ == "__main__":
    app.run()
