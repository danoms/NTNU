type_coming = {
        'note'      : 0,
        'duration'  : 1,
        'pause'     : 2
        }

def decode_note(name,debug=0):
    from itertools import cycle
    
    f = open(name,'r')
    data = f.readlines()
    note_arr = []
    duration_arr = []
    pause_arr = []
    octave = 0
    pause = 1
    
    choose_note = {
        'C':  1,
        'C#': 2,
        'Db': 2,
        'D':  3,
        'D#': 4,
        'Eb': 4,
        'E':  5,
        'F':  6,
        'F#': 7,
        'Gb': 7,
        'G':  8,
        'G#': 9,
        'Ab': 9,
        'A':  10,
        'A#': 11,
        'Bb': 11,
        'B':  12
        }

    choose_duration = {
        'W' : 1,
        'H' : 1/2,
        'Q' : 1/4,
        'E' : 1/8,
        'S' : 1/16,
        'P' : 1/100
        }
    exceptions = {
        '+' : 1,
        '-' : 2
        }
    excep_func = {
        1 : lambda x, y : x + y,
        2 : lambda x, y : x - y
        }
    job = {
        'in_exc'    : 1,
        'not_exc'   : 0
        }
    cycle_type = cycle(type_coming)
    next_cycle = next(cycle_type)
    even = 1
    temp = 0
    do_exc = 0
    pause = choose_duration['P']
    increase_temp = 0
    exception = 0
    counter = 0
    for line in data:
##        counter += 1
##        print('{} line {} counter\n {} next_cycle'.format(line, counter, next_cycle))
        if debug == 1:
            print (line)
        for next_char in line.split():
            exception = exceptions.get(next_char,0)
##            print(next_char)
##            print ('{} {}'.format(do_exc, 'do_exc'))
##            print('{} exception'.format(exception))
##            print('{} next_cycle'.format(next_cycle))
            if (exception > 0 and do_exc != 1):
                do_exc = 1
                saved_exc = exception
            elif next_cycle == 'note':
                if do_exc > 0:
                    octave = excep_func[saved_exc](octave,int(next_char))
                    do_exc = 0
                    exception = 0
                else:
                    next_cycle = next(cycle_type)
                    note_arr.append(choose_note.get(next_char,0)+ octave*12)
##                    print(note_arr[-1])
            elif next_cycle == 'duration':
                if do_exc > 0:
                    temp = excep_func[saved_exc](temp,choose_duration[next_char])
                    do_exc = 0
                    exception = 0
                else:
                    next_cycle = next(cycle_type)
                    duration_arr.append(choose_duration.get(next_char,0) + temp )
                    temp = 0
            elif next_cycle == 'pause':
##                print('{} next char \n {} '.format(next_char, next_cycle))
                if do_exc > 0:
                    temp = excep_func[saved_exc](temp,choose_duration[next_char])
                    do_exc = 0
##                    print('yes temp special {}'.format(temp))
                    exception = 0
##                    print('doing temp + ')
                else:
                    next_cycle = next(cycle_type)
##                    print('{} {}'.format(next_cycle, temp))
                    if temp > 0:
                        pause_arr.append(temp)
                        temp = 0
##                        print('yes')
##                        print ('doing special temp adding PAUSE')
                    else:
                        pause_arr.append(choose_duration['P'])
##                        print('doing normal P adding PAUSE')
##    print(pause_arr)
    return [ note_arr, duration_arr, pause_arr ]

def gen_note(name,debug=0):
    """calculate frequency, using american note notation"""
    [note_arr , duration_arr, pause_arr] = decode_note(name,debug)
    note_f_arr = []
    
    base_note = 440
    base_octave = 4
    base_nr = 10

    count_size = 0
    for note in note_arr:
        n = (4 - base_octave)*12 + note - base_nr
        note_f_arr.append(int(2**(n/12)*base_note))
        count_size += 1
        print(note_f_arr[-1])
    return [note_f_arr, duration_arr, pause_arr, count_size]

def gen_c(source, speed=1,debug=0):
    """generates c file, to include my music"""
    (note_arr, duration_arr, pause_arr, size) = gen_note(source,debug)

    f_clk = 14000000
    counter = 2**16
    base_sec = (f_clk/counter)*speed
    
    f_final = [f_clk / x for x in note_arr]
    f_final[:] = [int(x) for x in f_final]
##    print(f_final)
    duration_final = [base_sec * x for x in duration_arr]
    duration_final[:] = [int(x) for x in duration_final]

    pause_final = [(base_sec) * x for x in pause_arr]
    pause_final[:] = [int(x) for x in pause_final]

    all_arr = []
    all_arr.append(f_final)
    all_arr.append(duration_final)
    all_arr.append(pause_final)
    all_arr.append(size)

    

    sp = ' '
    var_type = 'sound'
    name = source.split('/')[-1].replace('.txt','')
    start_define = '#ifndef'+sp+name+'_H\n' + '#define' +sp+name+'_H\n\n'
    end_define = '#endif'
    output_dir = '../music/'
    extension = '.h'
    imports = '#include "../improved/game_types.h" \n\n'
    start = var_type+sp+name+ ' = {\n'
    include = ''
    for arr in all_arr:
        include += '\t' + str(arr).replace('[','{').replace(']','}')
        if arr != all_arr[-1]:
            include +=',\n'
        else:
            pass
    finish = '\n};\n\n'
    
##    print (include)
    
    
##    include = '\t' + str(f_final).replace('[','{').replace(']','}')

    
    c_file = imports + start_define + start + include + finish + end_define

    f = open(output_dir + name + extension ,'w')
    f.write(c_file)

    
    


