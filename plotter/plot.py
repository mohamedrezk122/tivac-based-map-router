import folium
data = []
with open('ddata.txt' ,'r') as file :

    for i in range(144):
        line = file.readline().split(',')

        data.append([ float(line[0]) ,float(line[1].replace('\n','')) ])

print(data)

def export_html( path ,  filename):
    map_ = folium.Map(path[0], zoom_start=13)
    folium.PolyLine(path, color='red').add_to(map_)

    map_.save(filename)

export_html(data , 'test.html')