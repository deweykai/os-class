f = open('/dev/pa2', 'r+');

test_data = 'hello there'

f.write(test_data)
f.seek(0)
recv_data = f.read(len(test_data))

assert recv_data == test_data
