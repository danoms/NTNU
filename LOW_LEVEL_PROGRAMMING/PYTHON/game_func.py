def read_wav_header(source = '../WAV/smb_world_clear.wav'):

    header_structure = {
        'begin'     : '',
        'file_size' : 0,
        'file_type' : '',
        'fmt'    : '',
        'length'    : 0,
        'format PCM/byte integer' : 0,
        'channels' : 0,
        'sample_rate' : 0,
        'more' : 0,
        'more2' : 0,
        'bits_per_sample' : 0,
        'data'  : '',
        'size' : 0
        }
    
    with open(source, 'rb') as f:
        data = f.read(44)
        header_structure['begin'] = data[0:4].decode('utf-8')
        header_structure['file_size'] = int.from_bytes(data[4:8],byteorder='little')
        header_structure['file_type'] = data[8:12].decode('utf-8')
        header_structure['fmt'] =  data[12:16].decode('utf-8')
        header_structure['length'] = int.from_bytes(data[16:20],byteorder='little')
        header_structure['format PCM/byte integer'] = int.from_bytes(data[20:22],byteorder='little')
        header_structure['channels'] = int.from_bytes(data[22:24],byteorder='little')
        header_structure['sample_rate'] = int.from_bytes(data[24:28],byteorder='little')
        header_structure['more'] = int.from_bytes(data[28:32],byteorder='little')
        header_structure['more2'] = int.from_bytes(data[32:34],byteorder='little')
        header_structure['bits_per_sample'] = int.from_bytes(data[34:36],byteorder='little')
        header_structure['data'] =  data[36:40].decode('utf-8')
        header_structure['size'] = int.from_bytes(data[40:44],byteorder='little')


        print(data)
        print(header_structure)

    
