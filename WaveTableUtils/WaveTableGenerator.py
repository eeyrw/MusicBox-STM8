import wave,struct
import os
from math import log2, pow

def noteToFreq(note):
    a = 440 #frequency of A (coomon value is 440Hz)
    return (a / 32) * (2 ** ((note - 9) / 12))
 
def readWaveSamples(file_path):
    sampleArray=[]
    f = wave.open(file_path,"rb")
    params = f.getparams()
    nchannels, sampwidth, framerate, nframes = params[:4]
    if nchannels!=1:
        print("Must be mono wave file.")
        return -1
    if sampwidth!=2:
        print("Must be 16bit sample width.")
        return -1        
    if framerate!=32000:
        print("Sample rate must be 32000 samples/s")
        return -1        

    for i in range(0,nframes):
        waveData = f.readframes(1)
        data = struct.unpack("<h", waveData)
        sampleArray.append(int(data[0]))
    f.close()
    return sampleArray

def calcIncrement(baseFreq,targetFreq):
    return targetFreq/baseFreq   

def exportToSourceFile(sampleName,attackSamples,loopSamples,fileDir,sampleWidth):
    waveTableIdentifer="WaveTable_%s"%sampleName
    attackLen=len(attackSamples)
    loopLen=len(loopSamples)
    totalLen=attackLen+loopLen
    if sampleWidth==1:
        sampleType="int8_t"
        attackSamples=[int(sample/256) for sample in attackSamples]
        loopSamples=[int(sample/256) for sample in loopSamples]
    elif sampleWidth==2:
        sampleType="int16_t"

    hFilePath=os.path.join(fileDir,"%s.h"%waveTableIdentifer)
    cFilePath=os.path.join(fileDir,"%s.c"%waveTableIdentifer)
    
    with open(hFilePath,'w') as hFile:
        hFile.write("#ifndef __%s__\n#define __%s__\n"%(str.upper(waveTableIdentifer),str.upper(waveTableIdentifer)))
        hFile.write("#include <stdint.h>\n")
        hFile.write("#define %s_LEN %d\n"%(str.upper(waveTableIdentifer),totalLen))
        hFile.write("#define %s_ATTACK_LEN %d\n"%(str.upper(waveTableIdentifer),attackLen))
        hFile.write("#define %s_LOOP_LEN %d\n"%(str.upper(waveTableIdentifer),loopLen))
        hFile.write("extern const %s %s[%s_LEN];\n"%(sampleType,waveTableIdentifer,str.upper(waveTableIdentifer)))
        hFile.write("extern const uint16_t %s_Increment[];\n"%waveTableIdentifer)
        hFile.write("#endif")

    with open(cFilePath,'w') as cFile:
        cFile.write("#include <stdint.h>\n#include <%s.h>\n"%waveTableIdentifer)
        cFile.write("const %s %s[%s_LEN]={\n"%(sampleType,waveTableIdentifer,str.upper(waveTableIdentifer)))
        newLineCounter=0
        cFile.write("// Attack Samples:\n")
        for sample in attackSamples:
            cFile.write("%8d,"%sample)
            if newLineCounter>8:
                newLineCounter=0
                cFile.write("\n")
            else:
                newLineCounter+=1
        cFile.write("\n// Loop Samples:\n")
        for sample in loopSamples:
            cFile.write("%8d,"%sample)
            if newLineCounter>8:
                newLineCounter=0
                cFile.write("\n")
            else:
                newLineCounter+=1        
        cFile.write("};\n")
        cFile.write("const uint16_t %s_Increment[]={\n"%waveTableIdentifer)
        newLineCounter=0
        for i in range(57,120):
            cFile.write("%5d,"%(calcIncrement(523.25,noteToFreq(i))*255))
            if newLineCounter>8:
                newLineCounter=0
                cFile.write("\n")
            else:
                newLineCounter+=1        
        cFile.write("};\n")            



def main():
    attackSamples=readWaveSamples("./WaveTableUtils/Celesta_C5_ATTACK.wav")	
    loopSamples=readWaveSamples("./WaveTableUtils/Celesta_C5_LOOP.wav")
    exportToSourceFile("Celesta_C5",attackSamples,loopSamples,'./WaveTableUtils/',1)
    
if __name__ == "__main__":
	main()