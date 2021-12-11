#!/user/bin/env python
# -*- coding:utf-8 -*-

# Author:				Weitao Sun
# Created on:			###### Thu Nov 11 11:43:01 PST 2021
# Last modify on:		###### Thu Nov 11 11:43:06 PST 2021
# Purpose: 				Used to run on a server to receve the data comes from Raspberry Pi and store it
#                       Also handle the http request from client to send back the stored data
#                       Receive the client control command and send it to the Raspberry Pi

from flask import Flask, jsonify
from flask import request
from flask.scaffold import F
from gevent import pywsgi
import random
import logging
import time
import copy
import json

MAX_LOG_BUFFER_LENGTH = 10
logBuff = []

tankRemain = 0
waterRemain = 0
bowlAmount = 0
bowlThreshold = 100
autoAmount = 100
weightPerQuarter = 10
targetAmount = 30
frequency = 12

def setLogBuf(str):
    if len(logBuff) == 10:
        logBuff.pop(0)
    tempDic = {}
    tempDic["time"] = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    tempDic["msg"] = str
    logBuff.append(tempDic)


logging.basicConfig(filename='logs.log',
                    filemode='a',
                    format='%(asctime)s - %(name)s - %(levelname)s -%(module)s:  %(message)s',
                    datefmt='%Y-%m-%d %H:%M:%S %p',
                    level=10)

app = Flask(__name__)


@app.route('/feed', methods=['POST'])
def doFeed():
    print(bowlAmount)
    # the response is a json
    # isSuccess:    bool        True means success
    # tankRemain:   int         a int represent the percent of food remaining in the food tank
    # bowlAmount:   int         a int number represent the current food's weight in the bowl
    # failType:    str          if feed fail, this used to identify the fail reason: "No need feed"; "No enough food"
    # TODO
    # send a cmd to Raspberry Pi and return some info
    tankRemain = int(round(random.random(),2)*100)
    failMsg = ""
    global cmdNum
    if targetAmount - weightPerQuarter > bowlAmount:
        cmdNum = int((targetAmount - bowlAmount)/weightPerQuarter)
        isSuccess = True
    else:
        isSuccess = False
        failMsg = "No need to feed, bowl still have " + str(bowlAmount) + "g food"

    resMsg = {
        "isSuccess": isSuccess,
        "tankRemain": tankRemain,
        "bowlAmount": bowlAmount,
        "failType" : failMsg
    }



    logStr = "Manual Feed,\nTank remain: " + str(tankRemain) + "%\nCurrent bowl amount: " + str(bowlAmount) + "g\n";
    logging.info(logStr)
    setLogBuf(logStr)

    if tankRemain < 0.15:
        logging.warning("Low tank remain, less thant 15%")
        setLogBuf("WARNING:     Low tank remain, less thant 15%")
    return jsonify(resMsg)

@app.route('/getFre', methods=['GET'])
def getFre():
  return jsonify(frequency)

@app.route('/setFre', methods=['POST'])
def setFre():
  global frequency
  data = json.loads(request.get_data())
  frequency = int(data)
  
  logStr = "Auto-Feed period has been set to : " + str(frequency) + "h\n";
  logging.info(logStr)
  setLogBuf(logStr)
  print(logStr)
  
  return jsonify("")


@app.route('/getAmount', methods=['GET'])
def getAmount():
  return jsonify(int(targetAmount/weightPerQuarter))

@app.route('/setAmount', methods=['POST'])
def setAmount():
  global targetAmount
  data = json.loads(request.get_data())
  targetAmount = int(data)
  
  
  logStr = "Auto-Feed amount has been set to : " + str(targetAmount) + "g\n";
  logging.info(logStr)
  setLogBuf(logStr)
  print(logStr)
  
  return jsonify("")


@app.route('/logs', methods=['GET'])
def getLog():
    temp = copy.deepcopy(logBuff)
    temp.reverse()
    return jsonify(temp)

@app.route('/getcmd', methods=['GET'])
def getcmd():
    #global cmdNum
    #print(cmdNum)
    return jsonify(cmdNum)

@app.route('/reset', methods=['GET'])
def reset():
    global cmdNum
    cmdNum = 0
    return jsonify(cmdNum)

@app.route('/data', methods=['POST'])
def getData():
    global waterRemain, tankRemain, bowlAmount
    data = json.loads(request.get_data()).split()
    waterRemain = int(data[0])
    tankRemain = int(data[1])
    bowlAmount = int(data[2])
    return jsonify("")

if __name__ == '__main__':
    global cmdNum
    cmdNum = 0
    server = pywsgi.WSGIServer(('0.0.0.0', 5000), app)
    server.serve_forever()
