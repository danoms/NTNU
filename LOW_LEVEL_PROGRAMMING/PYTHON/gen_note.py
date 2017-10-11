f_sampling  = 44100
f_note = 441
volume = 10

def gen_note():
	output_arr = '\t'
	samples_per_T = int(f_sampling/f_note)

	for i in range(int(samples_per_T/2)):
		output_arr += '0' + ','
		if i % 20 == 0:
			output_arr += '\n\t'
	for i in range(int(samples_per_T/2)):
		output_arr += str(volume)
		if i != int(samples_per_T/2)-1:
			output_arr += ','
		if i % 20 == 0:
			output_arr += '\n\t'

	print(output_arr)
	return output_arr, int(samples_per_T)

def create_c():
	data, size = gen_note()

	start_template = 'int size = ' + str(size) + ';\nint sample_note_A[] = {\n'
	data = str(data)
	finish = '\n};'
	with open('sample_note_A.h','w') as f:
		f.write(start_template + data + finish)


print('creating file ...')
create_c()
print('finished!!!')