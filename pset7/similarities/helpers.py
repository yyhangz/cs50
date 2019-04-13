from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    alist = a.splitlines()
    blist = b.splitlines()
    result = []
    for line in alist:
        if line in blist and line not in result:
            result.append(line)
    return result


def sentences(a, b):
    """Return sentences in both a and b"""
    alist = sent_tokenize(a, language='english')
    blist = sent_tokenize(b, language='english')
    result = []
    for line in alist:
        if line in blist and line not in result:
            result.append(line)
    return result


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    alist = []
    result = []
    for i in range(len(a) - n + 1):
        acopy = a
        alist.append(acopy[i:(i + n)])
    for i in range(len(b) - n + 1):
        bcopy = b
        bsub = bcopy[i:(i + n)]
        if bsub in alist and bsub not in result:
            result.append(bsub)
    return result
