# source = 

def gen_sample(source='../WAV/smb_world_clear.wav', destination = 'sample_tst.h'):
    import wave
    print('loading ' + source)
    w = wave.open(source,'r')
    a = w.readframes(1)

    start = 'int sample_arr[] = { '
    include = ''
    counter = 0
    while a:
        counter += 1
        rez = int.from_bytes(a,byteorder='little') >> 4
        include += str(rez) + ','
        if counter > 20:
            counter = 0
            include += '\n'
        a = w.readframes(1)


    finish = start + include + '};\n'

    with open(destination,'w') as filez:
        print('writing to ' + destination)
        filez.write(finish) 

    print('all finished!!')



def read_header_info():
    pass
        
