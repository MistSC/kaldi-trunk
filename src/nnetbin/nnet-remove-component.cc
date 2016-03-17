// nnetbin/nnet-remove-component.cc

#include <string>
#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "nnet/nnet-nnet.h"

int main(int argc, char *argv[]) {
  try {
    using namespace kaldi;
    using namespace kaldi::nnet1;
    typedef kaldi::int32 int32;

    const char *usage =
        "Remove compoennt of neural networks\n"
        "Usage:  nnet-reomove-component [options] <model-in> <component index> <model-out>\n"
        "e.g.:\n"
        " nnet-reomove-component --binary=false nnet.1 1 nnet.2\n";
    
    ParseOptions po(usage);
    

    bool binary_write = true;
    po.Register("binary", &binary_write, "Write output in binary mode");


    po.Read(argc, argv);

    if (po.NumArgs() != 3 ) {
      po.PrintUsage();
      exit(1);
    }

    std::string model_in_filename = po.GetArg(1);
    std::string component_index = po.GetArg(2);
    std::string model_out_filename = po.GetArg(3);
    int com_index = std::atoi( component_index.c_str() );

    //read the first nnet
    KALDI_LOG << "Reading " << model_in_filename;
    Nnet nnet; 
    bool binary_read;
    Input ki(model_in_filename, &binary_read);
    nnet.Read(ki.Stream(), binary_read);

    if(com_index <= 0)
    {
      KALDI_LOG<< "Remove last component";
      nnet.RemoveLastComponent();
    }
    else
    {
      KALDI_LOG<< "Remove "<< component_index << "th component";
      nnet.RemoveComponent(com_index);
    }
    KALDI_LOG<<"Component has been removed";
    //finally write the nnet to disk
    Output ko(model_out_filename, binary_write);
    nnet.Write(ko.Stream(), binary_write);
    

    KALDI_LOG << "Written model to " << model_out_filename;
    return 0;
  } 
  catch(const std::exception &e) 
  {
    std::cerr << e.what() << '\n';
    return -1;
  }
}


