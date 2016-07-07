// featbin/outer-product-feats.cc


#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "feat/feature-functions.h"
//#include "matrix/kaldi-matrix.h"



int main(int argc, char *argv[]) {
  try {
    using namespace kaldi;

    const char *usage =
        "Outer product features for each frame\n"
        "Usage: outer-product-feats [options] in-rspecifier out-wspecifier\n";
    ParseOptions po(usage);

    po.Read(argc, argv);
    if (po.NumArgs() != 2) {
      po.PrintUsage();
      exit(1);
    }

    std::string rspecifier = po.GetArg(1);
    std::string wspecifier = po.GetArg(2);

    BaseFloatMatrixWriter feat_writer(wspecifier);
    SequentialBaseFloatMatrixReader feat_reader(rspecifier);
    for (; !feat_reader.Done(); feat_reader.Next()) {
      std::string key = feat_reader.Key();
      const Matrix<BaseFloat> &feats  = feat_reader.Value();

      if (feats.NumRows() == 0) {
        KALDI_WARN << "Empty feature matrix for key " << key;
        continue;
      }

      Matrix<BaseFloat> new_feats;
      ApplyOuterProductFeats(1.0, feats, feats, &new_feats);
      feat_writer.Write(key, new_feats);
    }
    return 0;
  } catch(const std::exception &e) {
    std::cerr << e.what();
    return -1;
  }
}


