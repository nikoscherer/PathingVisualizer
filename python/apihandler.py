import requests
import json
import sys

import types

wayFilter = dict()

def request(min_lon, max_lon, min_lat, max_lat):
    highways = wayFilter["drive"]
    
    query = f"""
        [out:json];
        way[highway~"^({highways})$"]({min_lat}, {min_lon}, {max_lat}, {max_lon});
        out body;
        """
    
    response = apiCall(query);
    
    if response.status_code != 200:
        print(f"Error code {response.status_code}")
        return
    
    print(response.json())

            
def apiCall(query):
    return requests.get("http://overpass-api.de/api/interpreter", params={'data': query})


def initWayFilter():
    global wayFilter
    
    wayFilter["drive"] = "motorway|trunk|primary|secondary|tertiary|unclassified|residential|living_street"
    

def init():
    initWayFilter()