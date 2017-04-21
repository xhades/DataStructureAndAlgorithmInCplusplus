from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords

from collections import defaultdict
from itertools import chain
from tqdm import tqdm

f = open('document.txt')
sentence = [line.strip() for line in f if line.strip() != ""]
f.close()

document = " ".join(sentence)

words_tokenized = [word.lower() for word in word_tokenize(document)]

normal_english_stopwords = stopwords.words('english')
extra_english_stopwords = ["n't", "'m", "'s", "'t"]
english_stopwords = list(chain(normal_english_stopwords, extra_english_stopwords))
words_filter_stopwords = [word for word in words_tokenized if not word in english_stopwords]

english_punctuations = [',', '.', ':', ';', '?', '(', ')', '[', ']', '&', '!', '*', '@', '#', '$', '%', "''", '``', '--']
words_filter_stopwords_and_filter_punctuations = [word for word in words_filter_stopwords if not word in english_punctuations]

print("[+] word frequency compute ...")
dd = defaultdict(int)
for word in tqdm("".join(words_filter_stopwords_and_filter_punctuations)):
    if dd[word] == 0:
        dd[word] = 1
    else:
        dd[word] += 1
print("[+] compute done !")

f = open('word frequency.txt', 'w+')
for k, v in dd.items():
    f.write(k)
    f.write(' : ')
    f.write(str(v))
    f.write('\n')
f.close
