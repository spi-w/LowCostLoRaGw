# %%
from flask import Flask,render_template, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://william:arEna123@10.99.0.103/Test2'
db = SQLAlchemy(app)

class Data(db.Model):
    id = db.Column(db.Integer,primary_key=True)
    ptype = db.Column(db.Integer, nullable=False)
    gateway_eui = db.Column(db.Integer, nullable=False)
    node_eui = db.Column(db.Integer, nullable=False)
    snr = db.Column(db.Integer, nullable=False)
    rssi = db.Column(db.Integer, nullable=False)
    cr = db.Column(db.Integer, nullable=False)
    datarate = db.Column(db.Integer, nullable=False)
    time = db.Column(db.DateTime, nullable=False)
    data = db.Column(db.String(100), nullable=False)

def add_array(array):
    try :
        array = Data(ptype = array["type"],
                     gateway_eui = array["gateway_eui"],
                     node_eui = array["node_eui"],
                     snr = array["snr"],
                     rssi = array["rssi"],
                     cr = array["cr"],
                     datarate = array["datarate"],
                     time = array["time"],
                     data = array["data"])
        db.session.add(array)
        db.session.commit()
    except Exception as e:
        print("SQLAlchemy : cannot add new array to the DB: " + str(e))

