def gen_note(NOTE=441):
    """generates note"""    
    f_sample = 4410
    f_note = NOTE
    nr_of_samples = int(f_sample/f_note)
    sec = f_note
    note_arr = ''
    for j in range(0, sec):
        for i in range(0,int(nr_of_samples/2)):
##            note_arr.append(0)
            note_arr += '0,' 
        for i in range(int(nr_of_samples/2), nr_of_samples):
##            note_arr.append(10)
            note_arr += '10'
            if ((j != sec-1) or (i != nr_of_samples-1)):
                note_arr += ','
        note_arr += '\n'
    return note_arr
##    f = open('music.txt', 'w')
##    f.write(str(note_arr))
    
    
def gen_sample():
    """generate sample"""
    sample_arr = gen_note(44)
    sample_arr += ',' + gen_note(88)
##    sample_arr.extend(gen_note(800))
##    sample_arr.extend(gen_note(500))
##    sample_arr.extend(gen_note(600))
##    sample_arr.extend(gen_note(700))

##    f = open('music.txt','w')
##    f.write(str(sample_arr).replace(',','')[1:-1])
    return sample_arr

def create_c_file():
    start = "int sample_music[]= {\n"
    note_samples = gen_sample()
    string = start + note_samples + '};\n'
    string += 'int sample_music_limit = 4410*2;'
    f = open('music2.h','w')
    f.write(string)
    
