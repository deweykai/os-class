def test_read():
	f = open('/dev/pa2', 'rb+');
	test_data = b'hello there'
	f.write(test_data)
	f.seek(0)
	recv_data = f.read(len(test_data))
	assert recv_data == test_data
	f.close()

def test_seek_before():
	f = open('/dev/pa2', 'rb+')
	f.seek(-1)
	f.close()

def test_seek_end():
	f = open('/dev/pa2', 'rb+')
	f.seek(-1, 2)
	f.close()

def test_seek_after():
	f = open('/dev/pa2', 'rb+')
	f.seek(1025)
	f.close()

def test_write_lots():
	s = bytes('banana_smoothie '* 200, 'utf-8')
	f = open('/dev/pa2', 'rb+')
	f.seek(10)
	f.write(s)
	f.close()

def offset_read_write():
	s = b'taco sunday'
	f = open('/dev/pa2', 'rb+')
	f.seek(20)
	f.write(s)
	f.close()
	f = open('/dev/pa2', 'rb+')
	f.seek(20)
	new_s = f.read(len(s))
	assert s == new_s

#test_read()
#test_seek_before()
#test_seek_end()
#test_seek_after()
#test_write_lots() # gets stuck in loop
#offset_read_write()
