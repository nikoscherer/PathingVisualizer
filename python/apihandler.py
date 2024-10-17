import requests
import json
import sys

def request(min_lon, max_lon, min_lat, max_lat):
    
    nodes = {}

    
    query = f"""
    [out:json];
    way[highway~"^(motorway|trunk|primary|secondary|tertiary|residential|unclassified)$"]({min_lat}, {min_lon}, {max_lat}, {max_lon})->.ways;
    (
    node(w.ways);
    );
    out body;
    """
    
    # NOT RIGHT WAY TO GET NEIGHBORS
    query2 = f"""
        [out:json];
        way[highway~"^(motorway|trunk|primary|secondary|tertiary|residential|unclassified)$"]({min_lat}, {min_lon}, {max_lat}, {max_lon});
        out body;
    """
    
    response = apiCall(query)

    if response.status_code == 200:
        data = response.json()
        
        for node in data['elements']:
            nodes[node['id']] = (node['id'], node['lon'], node['lat'], list([]))

        response2 = apiCall(query2)
        
        data2 = response2.json()
        
        if response2.status_code == 200:
            for way in data2['elements']:
                for nID in list(way['nodes']):
                    if nID in nodes:
                        for n in way['nodes']:    
                            nodes[nID][3].append(n)
        else:
            print("Error:", response.status_code)
            return -1      

        return list(nodes.values())

    else:
        print("Error:", response.status_code)
        return -1  
            
def apiCall(query):
    return requests.get("http://overpass-api.de/api/interpreter", params={'data': query})