import math
import sys
import time

import metapy
import pytoml

class PL2Ranker(metapy.index.RankingFunction):
    """
    Create a new ranking function in Python that can be used in MeTA.
    """
    def __init__(self, some_param=1.0):
        self.param = some_param
        # You *must* call the base class constructor here!
        super(PL2Ranker, self).__init__()

    def score_one(self, sd):
        """
        You need to override this function to return a score for a single term.
        For fields available in the score_data sd object,
        @see https://meta-toolkit.org/doxygen/structmeta_1_1index_1_1score__data.html
        """
        count_t_Q = sd.query_term_weight
        count_t_D = sd.doc_term_count
        count_t_C = sd.corpus_term_count
        avgdl = sd.avg_dl
        N = sd.num_docs
        doc_size = sd.doc_size
        
        lambd = N/count_t_C
        tfn = count_t_D * math.log2(1 + self.param * avgdl / doc_size)
        
        score = count_t_Q * (tfn * math.log2(tfn * lambd) + math.log2(math.e)*(1/lambd-tfn) + 0.5*math.log2(2*math.pi*tfn)) / (tfn+1)
        
        if lambd < 1 or tfn <= 0:
            return 0
        
        
        return score


def load_ranker(cfg_file):
    """
    Use this function to return the Ranker object to evaluate.

    The parameter to this function, cfg_file, is the path to a
    configuration file used to load the index. You can ignore this, unless
    you need to load a ForwardIndex for some reason...
    """
    return PL2Ranker(1.72)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: {} config.toml".format(sys.argv[0]))
        sys.exit(1)

    cfg = sys.argv[1]
    print('Building or loading index...')
    idx = metapy.index.make_inverted_index(cfg)
    ranker = load_ranker(cfg)
    ev = metapy.index.IREval(cfg)

    with open(cfg, 'r') as fin:
        cfg_d = pytoml.load(fin)

    query_cfg = cfg_d['query-runner']
    if query_cfg is None:
        print("query-runner table needed in {}".format(cfg))
        sys.exit(1)

    start_time = time.time()
    top_k = 10
    query_path = query_cfg.get('query-path', 'queries.txt')
    query_start = query_cfg.get('query-id-start', 0)

    query = metapy.index.Document()
    print('Running queries')
    with open(query_path) as query_file:
        for query_num, line in enumerate(query_file):
            query.content(line.strip())
            results = ranker.score(idx, query, top_k)
            avg_p = ev.avg_p(results, query_start + query_num, top_k)
            print("Query {} average precision: {}".format(query_num + 1, avg_p))
    print("Mean average precision: {}".format(ev.map()))
    print("Elapsed: {} seconds".format(round(time.time() - start_time, 4)))
