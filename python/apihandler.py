import requests
import json

def request():
    
    nodes = set()
    
    min_lat = 45.013512
    max_lat = 45.018908
    min_lon = -93.283222
    max_lon = -93.282520

    query = f"""
    [out:json];
    way[highway~"^(motorway|trunk|primary|secondary|tertiary|residential|unclassified)$"]({min_lat}, {min_lon}, {max_lat}, {max_lon})->.ways;
    (
    node(w.ways);
    );
    out body;
    """
    
    response = apiCall(query)

    if response.status_code == 200:
        data = response.json()

        print(json.dumps(data, indent=2))
        
        #nodes = getNodes(data)

    else:
        print("Error:", response.status_code)
            
def apiCall(query):
    return requests.get("http://overpass-api.de/api/interpreter", params={'data': query})