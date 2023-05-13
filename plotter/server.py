from flask import Flask, render_template, jsonify
import folium
import serial

app = Flask(__name__)

file = open('data.txt', 'a') # Open a file in append mode


# map variables 
dest_lat       = 30.0587530983    # destination latitude  
dest_lon       = 31.2736539054    # destination longitude
center_lat     = 30.0653703       # center of the map lat
center_lon     = 31.2787172       # center of map longitude
location_lon   = 31.2787172       # current location longitude
location_lat   = 30.0653703       # current location latitude
zoom_level     = 18               # map zoom level
past_valid_lat = location_lat
past_valid_lon = location_lon
port = "/dev/ttyUSB1"
baudrate = 9600 
ser = serial.Serial(port , baudrate=baudrate)


def filter_incomings(ser):
    line = ser.readline()
    line = line.decode("utf-8")
    print("line:" , line)
    if line and len(line.split(",")) == 2 :
        lat = float(line.split(",")[0])
        temp_lat = lat//100
        temp_lat = temp_lat+ (lat/100 - temp_lat)*(100/60 )
        lon = float(line.split(",")[1])
        temp_lon = lon//100
        temp_lon = temp_lon+ (lon/100 - temp_lon)*(100/60 )

        return temp_lat , temp_lon
    return past_valid_lat ,past_valid_lon

# a function to render map 
@app.route('/map')
def render_the_map():
    return render_template('test.html' , center_lon = center_lon, center_lat = center_lat, 
                                         loc_lon    = location_lon   ,  loc_lat   = location_lat , 
                                         dest_lon   = dest_lon  , dest_lat   = dest_lat, 
                                         zoom_level = zoom_level)

# function to update the location 
@app.route('/update')
def update():
    global location_lon , location_lat , past_valid_lon, past_valid_lat

    location_lat , location_lon =  filter_incomings(ser)
    if (location_lat> 30 and location_lon > 31 ):
        past_valid_lon = location_lon
        past_valid_lat = location_lat

    else:
        location_lat = past_valid_lat
        location_lon = past_valid_lon


    print(location_lat , location_lon) 
    file.write(f"{location_lat} , {location_lon} \n")
    updated_data = {"loc_lon": location_lon, "loc_lat": location_lat}
    return jsonify(updated_data)

if __name__ == '__main__':
    app.run(debug=False)
    file.close()