#include <cppjieba/Jieba.hpp>

using namespace std;

const char * const DICT_PATH = "dict/jieba.dict.utf8";
const char * const MHH_PATH = "dict/hmm_model.utf8";
const char * const USER_DICT_PATH = "dict/user.dict.utf8";
const char * const IDF_PATH = "dict/idf.utf8";
const char * const STOP_WORD_PATH = "dict/stop_words.utf8";

int main(int argc, char ** argv) {
    cppjieba::Jieba jieba(
        DICT_PATH,
        MHH_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH
    );

    vector<string> words;
    vector<cppjieba::Word> jieba_words;
    string str;
    string result;

    str = "spaCy是一个Python自然语言处理工具包，诞生于2014年年中，号称“Industrial-Strength Natural Language Processing in Python”，是具有工业级强度的Python-NLP工具包。spaCy里大量使用了Cython来提高相关模块的性能，这个区别于学术性质更浓的Python-NLTK， 因此具有了业界应用的实际价值。";
    cout << "[+] Cut With HMM" << endl;
    jieba.Cut(str, words, true);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    return EXIT_SUCCESS;
}
