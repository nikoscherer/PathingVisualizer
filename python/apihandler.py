import requests
import json

def request():
    
    min_lat = 45.013512
    max_lat = 45.018908
    min_lon = -93.283222
    max_lon = -93.282520

    query = f"""
    [out:json];
    node(757537374);
    way(bn);
    out body;
    """

    response = requests.get("http://overpass-api.de/api/interpreter", params={'data': query})

    if response.status_code == 200:
        data = response.json()

        print(json.dumps(data, indent=2))
            

    else:
        print("Error:", response.status_code)
     