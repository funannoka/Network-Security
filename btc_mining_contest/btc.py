import hashlib
import random
import time
previousHeader = '15ad44909d7c00d5384e5a613fd6f132f7441a0'
nextTx = 'I, Rahul Dileep Jadhav, give Ifunanya Nnoka 10 BTC-282, on November18, 2016 2:52 am'
NMax = 100
maxNonce = 2**66
NM = int(input('Enter the number of bits to match: '))
while NM < NMax:
    start_time = time.time()
    Target = 2**(256-NM)
    difficulty = 2**NM
    nonce = random.randint(0,maxNonce)
    hash_i = hashlib.sha256(hashlib.sha256(str(previousHeader) + nextTx +str(nonce)).hexdigest()).hexdigest()
    end_time=time.time()
    elapsed_time = end_time - start_time
    if long(hash_i,16) < Target:
        print '\n\nFor number', NM, 'difficulty', difficulty
        print '\nMatching found', hash_i
        print '\nfor previousHeader=>', previousHeader
        print '\nfor => nextTx', nextTx
        print '\nFor nonce value', nonce
        print '\n Elapsed Time', elapsed_time
        print '\n CPU hash speed', nonce/elapsed_time
        NM += 1