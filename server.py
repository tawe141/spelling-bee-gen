import py_spelling_bee_gen
from flask import Flask
import gc

with open('english-words/words_alpha.txt', 'r') as f:
    lines = [i[:-1] for i in f.readlines()]  # last character is \n, which should be removed
    trie = py_spelling_bee_gen.TrieNode(lines)
del lines
gc.collect()

app = Flask(__name__)


@app.route('/')
def home():
    return {'msg': 'Simple NYTimes Spelling Bee solutions generator',
            'dictionary': 'https://github.com/dwyl/english-words'}


@app.route('/<mandatory>/<auxiliary>')
def search(mandatory: str, auxiliary: str):
    result = [i for i in trie.search(set(mandatory), set(auxiliary)) if len(i) >= 4]
    return {
        'success': 'true',
        'search_results': result
    }


if __name__ == "__main__":
    app.run()
