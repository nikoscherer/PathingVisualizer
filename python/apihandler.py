import requests
import json

def request(min_lon, max_lon, min_lat, max_lat):
    
    nodes = set()


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
        
        for node in data['elements']:
            nodes.add(node['id'])

        return list(nodes)
        
        #nodes = getNodes(data)
    else:
        print("Error:", response.status_code)
        return -1
            
def apiCall(query):
    return requests.get("http://overpass-api.de/api/interpreter", params={'data': query})