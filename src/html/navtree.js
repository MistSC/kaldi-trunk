var NAVTREE =
[
  [ "Kaldi", "index.html", [
    [ "Online Recognizers", "online_programs.html", [
      [ "About the Kaldi project", "about.html", [
        [ "What is Kaldi?", "about.html#about_what", null ],
        [ "The name Kaldi", "about.html#about_name", null ],
        [ "Kaldi's versus other toolkits", "about.html#about_compare", null ],
        [ "The flavor of Kaldi", "about.html#about_flavor", null ],
        [ "Status of the project", "about.html#about_status", null ],
        [ "Referencing Kaldi in papers", "about.html#about_reference", null ]
      ] ],
      [ "Other Kaldi-related resources (and how to get help)", "other.html", null ],
      [ "Downloading and installing Kaldi", "install.html", [
        [ "Dowloading Kaldi", "install.html#install_download", null ],
        [ "Installing Kaldi", "install.html#install_install", null ]
      ] ],
      [ "Software required to install and run Kaldi", "dependencies.html", [
        [ "Ideal computing environment", "dependencies.html#dependencies_environment", null ],
        [ "Bare minimum computing environment", "dependencies.html#dependencies_minimum", null ],
        [ "Software packages required", "dependencies.html#dependencies_packages", null ],
        [ "Software packages installed by Kaldi", "dependencies.html#dependencies_installed", null ]
      ] ],
      [ "Legal stuff", "legal.html", null ],
      [ "Kaldi tutorial", "tutorial.html", "tutorial" ],
      [ "Glossary of terms", "glossary.html", null ],
      [ "Data preparation", "data_prep.html", [
        [ "Introduction", "data_prep.html#data_prep_intro", null ],
        [ "Data preparation-- the \"data\" part.", "data_prep.html#data_prep_data", [
          [ "Files you need to create yourself", "data_prep.html#data_prep_data_yourself", null ],
          [ "Files you don't need to create yourself", "data_prep.html#data_prep_data_noneed", null ]
        ] ],
        [ "Data preparation-- the \"lang\" directory.", "data_prep.html#data_prep_lang", null ],
        [ "Contents of the \"lang\" directory", "data_prep.html#data_prep_lang_contents", null ],
        [ "Creating the \"lang\" directory", "data_prep.html#data_prep_lang_creating", null ],
        [ "Creating the language model or grammar", "data_prep.html#data_prep_grammar", null ]
      ] ],
      [ "The build process (how Kaldi is compiled)", "build_setup.html", [
        [ "Build process on Windows", "build_setup.html#build_setup_windows", null ],
        [ "How our configure script works (for UNIX variants)", "build_setup.html#build_setup_configure", null ],
        [ "Editing kaldi.mk", "build_setup.html#build_setup_editing", null ],
        [ "Targets defined by the Makefiles", "build_setup.html#build_setup_targets", null ],
        [ "Where do the compiled binaries go?", "build_setup.html#build_setup_output", null ],
        [ "How our Makefiles work", "build_setup.html#build_setup_make", null ],
        [ "Which platforms has Kaldi been compiled on?", "build_setup.html#build_setup_platforms", null ]
      ] ],
      [ "The Kaldi coding style", "style.html", null ],
      [ "History of the Kaldi project", "history.html", [
        [ "Acknowledgements", "history.html#history_ack", null ]
      ] ],
      [ "The Kaldi Matrix library", "matrix.html", [
        [ "Matrix and vector types", "matrix.html#matrix_sec_types", null ],
        [ "Symmetric and triangular matrices", "matrix.html#matrix_sec_sym", null ],
        [ "Sub-vectors and sub-matrices.", "matrix.html#matrix_sec_sub", null ],
        [ "Calling conventions for vectors and matrices", "matrix.html#matrix_sec_calling", null ],
        [ "Copying matrix and vector types", "matrix.html#matrix_sec_copy", null ],
        [ "Scalar products", "matrix.html#matrix_sec_scalar", null ],
        [ "Resizing", "matrix.html#matric_sec_resizing", null ],
        [ "Matrix I/O", "matrix.html#matrix_sec_io", null ],
        [ "Other matrix library functions", "matrix.html#matrix_sec_other", null ]
      ] ],
      [ "External matrix libraries", "matrixwrap.html", [
        [ "Overview", "matrixwrap.html#matrixwrap_summary", null ],
        [ "Basic Linear Algebra Subroutines (BLAS)", "matrixwrap.html#matrixwrap_blas", null ],
        [ "Linear Algebra PACKage (LAPACK)", "matrixwrap.html#matrixwrap_lapack", null ],
        [ "Automatically Tuned Linear Algebra Software (ATLAS)", "matrixwrap.html#matrixwrap_atlas", [
          [ "Installing ATLAS (on Windows)", "matrixwrap.html#matrixwrap_atlas_install_windows", null ],
          [ "Installing ATLAS (on Linux)", "matrixwrap.html#matrixwrap_atlas_install_linux", null ]
        ] ],
        [ "Intel Math Kernel Library (MKL)", "matrixwrap.html#matrixwrap_mkl", null ],
        [ "OpenBLAS", "matrixwrap.html#matrixwrap_openblas", null ],
        [ "Java Matrix Package (JAMA)", "matrixwrap.html#matrixwrap_jama", null ],
        [ "Linking errors you might encounter", "matrixwrap.html#matrixwrap_linking_errors", [
          [ "f2c or g2c errors", "matrixwrap.html#matrix_err_f2c", null ],
          [ "CLAPACK linking errors", "matrixwrap.html#matrix_err_clapack", null ],
          [ "BLAS linking errors", "matrixwrap.html#matrix_err_blas", null ],
          [ "cblaswrap linking errors", "matrixwrap.html#matrix_err_cblaswrap", null ],
          [ "Missing the ATLAS implementation of BLAS", "matrixwrap.html#matrix_err_atl_blas", null ],
          [ "Missing the ATLAS implementation of (parts of) CLAPACK", "matrixwrap.html#matrix_err_atl_clapack", null ]
        ] ]
      ] ],
      [ "The CUDA Matrix library", "cudamatrix.html", null ],
      [ "Kaldi I/O mechanisms", "io.html", "io" ],
      [ "Kaldi logging and error-reporting", "error.html", [
        [ "Overview", "error.html#error_overview", null ],
        [ "Assertions in Kaldi", "error.html#error_assertions", null ],
        [ "Exceptions thrown by KALDI_ERR", "error.html#error_exceptions", null ],
        [ "Compile-time assertions in Kaldi", "error.html#error_compile_time_assertions", null ]
      ] ],
      [ "Parsing command-line options", "parse_options.html", [
        [ "Introduction", "parse_options.html#parse_options_introduction", null ],
        [ "Example of parsing command-line options", "parse_options.html#parse_options_example", null ],
        [ "Implicit command-line arguments", "parse_options.html#parse_options_implicit", null ]
      ] ],
      [ "Other Kaldi utilities", "util.html", [
        [ "Text utilities", "util.html#util_sec_text", null ],
        [ "STL utilities", "util.html#util_sec_stl", null ],
        [ "Math utilities", "util.html#util_sec_math", null ],
        [ "Other utilities", "util.html#util_sec_other", null ]
      ] ],
      [ "Clustering mechanisms in Kaldi", "clustering.html", [
        [ "The Clusterable interface", "clustering.html#clustering_sec_intro", null ],
        [ "Clustering algorithms", "clustering.html#clustering_sec_algo", [
          [ "K-means and algorithms with similar interfaces", "clustering.html#clustering_sec_kmeans", null ],
          [ "Tree clustering algorithm", "clustering.html#clustering_sec_tree_cluster", null ]
        ] ]
      ] ],
      [ "HMM topology and transition modeling", "hmm.html", [
        [ "Introduction", "hmm.html#hmm_intro", null ],
        [ "HMM topologies", "hmm.html#hmm_topology", null ],
        [ "Pdf-classes", "hmm.html#pdf_class", null ],
        [ "Transition models (the TransitionModel object)", "hmm.html#transition_model", [
          [ "How we model transition probabilities in Kaldi", "hmm.html#transition_model_how", null ],
          [ "The reason for transition-ids etc.", "hmm.html#transition_model_mappings", null ],
          [ "Integer identifiers used by TransitionModel", "hmm.html#transition_model_identifiers", null ]
        ] ],
        [ "Training the transition model", "hmm.html#hmm_transition_training", null ],
        [ "Alignments in Kaldi", "hmm.html#hmm_alignment", null ],
        [ "State-level posteriors", "hmm.html#hmm_post", null ],
        [ "Gaussian-level posteriors", "hmm.html#hmm_gpost", null ],
        [ "Functions for converting HMMs to FSTs", "hmm.html#hmm_graph", [
          [ "GetHTransducer()", "hmm.html#hmm_graph_get_h_transducer", null ],
          [ "The HTransducerConfig configuration class", "hmm.html#hmm_graph_config", null ],
          [ "The function GetHmmAsFst()", "hmm.html#hmm_graph_get_hmm_as_fst", null ],
          [ "AddSelfLoops()", "hmm.html#hmm_graph_add_self_loops", null ],
          [ "Adding transition probabilities to FSTs", "hmm.html#hmm_graph_add_transition_probs", null ]
        ] ],
        [ "Reordering transitions", "hmm.html#hmm_reorder", null ],
        [ "Scaling of transition and acoustic probabilities", "hmm.html#hmm_scale", null ]
      ] ],
      [ "Decision tree internals", "tree_internals.html", [
        [ "Event maps", "tree_internals.html#treei_event_map", null ],
        [ "Statistics for building the tree", "tree_internals.html#treei_stats", null ],
        [ "Classes and functions involved in tree-building", "tree_internals.html#treei_func", [
          [ "Questions (config class)", "tree_internals.html#treei_func_questions", null ],
          [ "Lowest-level functions", "tree_internals.html#treei_func_low", null ],
          [ "Intermediate-level functions", "tree_internals.html#treei_func_intermediate", null ],
          [ "Top-level tree-building functions", "tree_internals.html#treei_func_top", null ]
        ] ]
      ] ],
      [ "How decision trees are used in Kaldi", "tree_externals.html", [
        [ "Introduction", "tree_externals.html#tree_intro", null ],
        [ "Phonetic context windows", "tree_externals.html#tree_window", null ],
        [ "The tree building process", "tree_externals.html#tree_building", null ],
        [ "PDF identifiers", "tree_externals.html#pdf_id", null ],
        [ "Context dependency objects", "tree_externals.html#tree_ctxdep", null ],
        [ "An example of a decision tree", "tree_externals.html#tree_example", null ],
        [ "The ilabel_info object", "tree_externals.html#tree_ilabel", null ]
      ] ],
      [ "Decoding graph construction in Kaldi", "graph.html", [
        [ "Overview of graph creation", "graph.html#graph_overview", null ],
        [ "Disambiguation symbols", "graph.html#graph_disambig", null ],
        [ "The ContextFst object", "graph.html#graph_context", null ],
        [ "Avoiding weight pushing", "graph.html#graph_weight", null ]
      ] ],
      [ "Decoding-graph creation recipe (test time)", "graph_recipe_test.html", [
        [ "Preparing the initial symbol tables", "graph_recipe_test.html#graph_symtab", null ],
        [ "Preparing the lexicon L", "graph_recipe_test.html#graph_lexicon", null ],
        [ "Preparing the grammar G", "graph_recipe_test.html#graph_grammar", null ],
        [ "Preparing LG", "graph_recipe_test.html#graph_lg", null ],
        [ "Preparing CLG", "graph_recipe_test.html#graph_clg", [
          [ "Making the context transducer", "graph_recipe_test.html#graph_c", null ],
          [ "Composing with C dynamically", "graph_recipe_test.html#graph_compose_c", null ],
          [ "Reducing the number of context-dependent input symbols", "graph_recipe_test.html#graph_change_ilabel", null ]
        ] ],
        [ "Making the H transducer", "graph_recipe_test.html#graph_h", null ],
        [ "Making HCLG", "graph_recipe_test.html#graph_hclg", null ],
        [ "Adding self-loops to HCLG", "graph_recipe_test.html#graph_selfloops", null ]
      ] ],
      [ "Decoding-graph creation recipe (training time)", "graph_recipe_train.html", [
        [ "Command-line programs involved in decoding-graph creation", "graph_recipe_train.html#graph_recipe_command", null ],
        [ "Internals of graph creation", "graph_recipe_train.html#graph_recipe_internal", null ]
      ] ],
      [ "Finite State Transducer algorithms", "fst_algo.html", [
        [ "Determinization", "fst_algo.html#fst_algo_det", [
          [ "Debugging determinization", "fst_algo.html#fst_algo_det_debug", null ],
          [ "Determinization in the log semiring", "fst_algo.html#fst_algo_det_log", null ]
        ] ],
        [ "Removing epsilons", "fst_algo.html#fst_algo_eps", null ],
        [ "Preserving stochasticity and testing it", "fst_algo.html#fst_algo_stochastic", null ],
        [ "Minimization", "fst_algo.html#fst_algo_minimization", null ],
        [ "Composition", "fst_algo.html#fst_algo_composition", null ],
        [ "Adding and removing disambiguation symbols", "fst_algo.html#fst_algo_disambig", null ]
      ] ],
      [ "Decoders used in the Kaldi toolkit", "decoders.html", [
        [ "The Decodable interface", "decoders.html#decodable_interface", null ],
        [ "SimpleDecoder: the simplest possible decoder", "decoders.html#decoders_simple", [
          [ "Interface of SimpleDecoder", "decoders.html#decoders_simple_itf", null ],
          [ "How SimpleDecoder works", "decoders.html#decoders_simple_workings", null ]
        ] ],
        [ "FasterDecoder: a more optimized decoder", "decoders.html#decoders_faster", null ],
        [ "BiglmDecoder: decoding with large language models.", "decoders.html#decoders_biglm", null ],
        [ "Lattice generating decoders", "decoders.html#decoders_lattice", null ]
      ] ],
      [ "Lattices in Kaldi", "lattices.html", [
        [ "Introduction", "lattices.html#lattices_intro", null ],
        [ "The Lattice type", "lattices.html#lattices_lattice", null ],
        [ "Compact lattices (the CompactLattice type)", "lattices.html#lattices_compact", [
          [ "Getting the raw lattice, and converting it into the final form.", "lattices.html#lattices_generation", null ]
        ] ],
        [ "Lattices in archives", "lattices.html#lattices_archives", null ],
        [ "Operations on lattices", "lattices.html#lattices_operations", [
          [ "Pruning lattices", "lattices.html#lattices_operations_pruning", null ],
          [ "Computing the best path through a lattice", "lattices.html#lattices_operations_best_path", null ],
          [ "Computing the N-best hypotheses", "lattices.html#lattices_operations_nbest", null ],
          [ "Language model rescoring", "lattices.html#lattices_operations_lmrescore", null ],
          [ "Probability scaling", "lattices.html#lattices_operations_scale", null ],
          [ "Lattice union", "lattices.html#lattices_union", null ],
          [ "Lattice composition", "lattices.html#lattices_operations_compose", null ],
          [ "Lattice interpolation", "lattices.html#lattices_operations_interp", null ],
          [ "Conversion of lattices to phones", "lattices.html#lattices_operations_phones", null ],
          [ "Lattice projection", "lattices.html#lattices_operations_project", null ],
          [ "Lattice equivalence testing", "lattices.html#lattices_operations_equivalent", null ],
          [ "Removing alignments from lattices", "lattices.html#lattices_operations_rmali", null ],
          [ "Error boosting in lattices", "lattices.html#lattices_operations_boost", null ],
          [ "Computing posteriors from lattices", "lattices.html#lattices_operations_post", null ],
          [ "Determinization of lattices", "lattices.html#lattices_operations_det", null ],
          [ "Computing oracle WERs from lattices", "lattices.html#lattices_operations_oracle", null ],
          [ "Adding transition probabilities to lattices", "lattices.html#lattices_operations_tprob", null ],
          [ "Converting lattices to FSTs", "lattices.html#lattices_operations_to_fst", null ],
          [ "Copying lattices", "lattices.html#lattices_operations_copy", null ]
        ] ],
        [ "N-best lists and best paths", "lattices.html#lattice_nbest", null ],
        [ "Times on lattices", "lattices.html#lattices_times", null ]
      ] ],
      [ "Acoustic modeling code", "model.html", [
        [ "Introduction", "model.html#model_intro", null ],
        [ "Diagonal GMMs", "model.html#model_diag", [
          [ "Individual GMMs", "model.html#model_diag_gmm", null ],
          [ "GMM-based acoustic model", "model.html#model_diag_am", null ],
          [ "Full-covariance GMMs", "model.html#model_full_gmm", null ]
        ] ],
        [ "Subspace Gaussian Mixture Models (SGMMs)", "model.html#model_sgmm", null ]
      ] ],
      [ "Feature extraction", "feat.html", [
        [ "Introduction", "feat.html#feat_intro", null ],
        [ "Computing MFCC features", "feat.html#feat_mfcc", null ],
        [ "Computing PLP features", "feat.html#feat_plp", null ],
        [ "Feature-level Vocal Tract Length Normalization (VTLN).", "feat.html#feat_vtln", null ]
      ] ],
      [ "Feature and model-space transforms in Kaldi", "transform.html", [
        [ "Introduction", "transform.html#transform_intro", null ],
        [ "Applying global linear or affine feature transforms", "transform.html#transform_apply", null ],
        [ "Speaker-independent versus per-speaker versus per-utterance adaptation", "transform.html#transform_perspk", null ],
        [ "Utterance-to-speaker and speaker-to-utterance maps", "transform.html#transform_utt2spk", null ],
        [ "Composing transforms", "transform.html#transform_compose", null ],
        [ "Silence weighting when estimating transforms", "transform.html#transform_weight", null ],
        [ "Linear Discriminant Analysis (LDA) transforms", "transform.html#transform_lda", null ],
        [ "Frame splicing", "transform.html#transform_splice", null ],
        [ "Delta feature computation", "transform.html#transform_delta", null ],
        [ "Heteroscedastic Linear Discriminant Analysis (HLDA)", "transform.html#transform_hlda", null ],
        [ "Global Semi-tied Covariance (STC) / Maximum Likelihood Linear Transform (MLLT) estimation", "transform.html#transform_mllt", null ],
        [ "Global CMLLR/fMLLR transforms", "transform.html#transform_cmllr_global", null ],
        [ "Linear VTLN (LVTLN)", "transform.html#transform_lvtln", null ],
        [ "Exponential Transform (ET)", "transform.html#transform_et", null ],
        [ "Cepstral mean and variance normalization", "transform.html#transform_cmvn", null ],
        [ "Building regression trees for adaptation", "transform.html#transform_regtree", null ]
      ] ],
      [ "Deep Neural Networks in Kaldi", "dnn.html", "dnn" ],
      [ "Online decoding in Kaldi", "online_decoding.html", [
        [ "Scope of online decoding in Kaldi", "online_decoding.html#online_decoding_scope", null ],
        [ "online decoding", "online_decoding.html#GMM-based", null ],
        [ "Decoders versus decoding programs", "online_decoding.html#online_decoding_decoders", null ],
        [ "Feature extraction in online decoding", "online_decoding.html#online_decoding_feature", null ],
        [ "Cepstral mean and variance normalization in online decoding", "online_decoding.html#online_decoding_cmvn", [
          [ "Freezing the state of CMN", "online_decoding.html#online_decoding_cmvn_freeze", null ]
        ] ],
        [ "Adaptation in online decoding", "online_decoding.html#online_decoding_adaptation", null ],
        [ "Use of multiple models in GMM-based online decoding", "online_decoding.html#online_decoding_models", null ],
        [ "Neural net based online decoding with iVectors", "online_decoding.html#online_decoding_nnet2", [
          [ "Example for using already-built online-nnet2 models", "online_decoding.html#online_decoding_nnet2_example", null ],
          [ "Example for using your own language model with existing online-nnet2 models", "online_decoding.html#online_decoding_nnet2_lm", null ],
          [ "Example for using a different vocabulary with existing online-nnet2 models", "online_decoding.html#online_decoding_nnet2_vocab", null ]
        ] ]
      ] ],
      [ "Keyword Search in Kaldi", "kws.html", [
        [ "Introduction", "kws.html#kws_intro", null ],
        [ "Typical Kaldi KWS system", "kws.html#kws_system", null ],
        [ "Proxy keywords", "kws.html#kws_proxy", null ],
        [ "Babel scripts", "kws.html#kws_scripts", [
          [ "A highlevel look", "kws.html#kws_scripts_highlevel", null ],
          [ "Prepare KWS data", "kws.html#kws_scripts_dataprep", null ],
          [ "Indexing and searching", "kws.html#kws_scripts_index_and_search", null ]
        ] ]
      ] ],
      [ "Parallelization in Kaldi", "queue.html", [
        [ "Introduction", "queue.html#parallelization_intro", null ],
        [ "Common interface of parallelization tools", "queue.html#parallelization_common", [
          [ "New-style options (unified interface)", "queue.html#parallelization_common_new", null ],
          [ "Example of configuring grid software with new-style options", "queue.html#parallelization_common_new_example", null ]
        ] ],
        [ "Parallelization using specific scripts", "queue.html#parallelization_specific", [
          [ "Parallelization using queue.pl", "queue.html#parallelization_specific_queue", null ],
          [ "Parallelization using run.pl", "queue.html#parallelization_specific_run", null ],
          [ "Parallelization using ssh.pl", "queue.html#parallelization_specific_ssh", null ],
          [ "Parallelization using slurm.pl", "queue.html#parallelization_specific_slurm", null ]
        ] ],
        [ "Setting up GridEngine for use with Kaldi", "queue.html#parallelization_gridengine", [
          [ "Installing GridEngine", "queue.html#parallelization_gridengine_installing", null ],
          [ "Configuring GridEngine", "queue.html#parallelization_gridengine_configuring", null ],
          [ "Configuring GridEngine (advanced)", "queue.html#parallelization_gridengine_configuring_advanced", null ],
          [ "Configuring GridEngine (adding nodes)", "queue.html#parallelization_gridengine_configuring_adding", null ]
        ] ],
        [ "Keeping your grid stable", "queue.html#parallelization_grid_stable", [
          [ "Keeping your grid stable (OOM)", "queue.html#parallelization_grid_stable_oom", null ],
          [ "Keeping your grid stable (NFS)", "queue.html#parallelization_grid_stable_nfs", null ],
          [ "Keeping your grid stable (general issues)", "queue.html#parallelization_grid_stable_misc", null ]
        ] ]
      ] ],
      [ "Online Audio Server", "online_programs.html#audio_server", [
        [ "Audio Data", "online_programs.html#audio_data", null ],
        [ "Recognition Results", "online_programs.html#results", null ],
        [ "Example Usage", "online_programs.html#usage", null ]
      ] ],
      [ "GStreamer plugin", "online_programs.html#gst_plugin", [
        [ "Installation", "online_programs.html#gst_plugin_installation", null ],
        [ "Usage through the command-line", "online_programs.html#usage_cli", null ],
        [ "Usage through GStreamer bindings", "online_programs.html#usage_gst", null ],
        [ "Overview of the online decoders' code", "online_programs.html#code_structure", null ]
      ] ]
    ] ],
    [ "Modules", "modules.html", "modules" ],
    [ "Namespaces", null, [
      [ "Namespace List", "namespaces.html", "namespaces" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", "namespacemembers_dup" ],
        [ "Functions", "namespacemembers_func.html", "namespacemembers_func" ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ],
        [ "Enumerator", "namespacemembers_eval.html", null ]
      ] ]
    ] ],
    [ "Classes", null, [
      [ "Class List", "annotated.html", "annotated" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", "functions_vars" ],
        [ "Typedefs", "functions_type.html", "functions_type" ],
        [ "Enumerations", "functions_enum.html", null ],
        [ "Enumerator", "functions_eval.html", null ],
        [ "Related Functions", "functions_rela.html", null ]
      ] ]
    ] ],
    [ "Files", null, [
      [ "File List", "files.html", "files" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", "globals_func" ],
        [ "Variables", "globals_vars.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_2nnet-component-test_8cc.html",
"arpa-file-parser-test_8cc.html#ad6523a106787ae90a963a9b351cb9d52",
"classfst_1_1CacheDeterministicOnDemandFst.html#a21e5b7babe07eeb31d1b2e98ffbcdc34",
"classfst_1_1LatticeDeterminizer.html#a2093a47bf8f58fa1038afe19e51330f0",
"classfst_1_1PushSpecialClass.html#a9de7936f9b2c05814a9d02a73fced9bb",
"classkaldi_1_1AccumDiagGmm.html#a766484031c247f04d917764ac543541e",
"classkaldi_1_1Barrier.html#a829cfcf0442499a0cef3933440ee9321",
"classkaldi_1_1ConstArpaLm.html#a5d379e894c6859ad0ce9c0d3ec4ebdd0",
"classkaldi_1_1CuMatrixBase.html#a5d4bcaf73515787cf3c40710e8557e48",
"classkaldi_1_1CuVector.html",
"classkaldi_1_1DecodableMatrixMappedOffset.html#a615dd6f29432bf8ca99098421aa15828",
"classkaldi_1_1EventMap.html#aeebfde63cc5c5b5198d87ddeece327f5",
"classkaldi_1_1GaussClusterable.html#a347c4dac4ae4302b103fd5124ef039ee",
"classkaldi_1_1IvectorExtractorStats.html#ad5da0494b3a3f4bc33ff83c9b5ff5b40",
"classkaldi_1_1LatticeHolder.html#a451470e654eb3d2df353b04866c3eec0",
"classkaldi_1_1LinearResample.html#ade487222cd2c687b15f4e69ffef0ed62",
"classkaldi_1_1MatrixExponential.html#a3779f55fe53eca5b225cd80f110d6b6c",
"classkaldi_1_1MleAmSgmmUpdaterMulti.html#a6a8699b17fe18611c891b692f1fcbebd",
"classkaldi_1_1OnlineGenericBaseFeature.html#aabd2d6d4abd68b234335e9d2736faf20",
"classkaldi_1_1ParseOptions.html#a64360011ed74cab078d5272ec2ecac37",
"classkaldi_1_1RandomAccessTableReaderScriptImpl.html#a6c54e3d48bb58ee781902eb65612a83d",
"classkaldi_1_1SequentialTableReaderScriptImpl.html#a1615968a92950438f6e67a28e9d56e5ca1273c8d92f00997cad7a2110f8628966",
"classkaldi_1_1SpMatrix.html#ae04e7ac955aaef3e7f297674950fcc58",
"classkaldi_1_1Tensor.html#aca3668aaa0f13ed32b570f8f44dbedea",
"classkaldi_1_1VectorBase.html#a12114a53f6c0a8f17deeb0dc6a208b67",
"classkaldi_1_1nnet1_1_1AffineTransform.html#a2c4b5bc54902d00793fad4b5f9f00133",
"classkaldi_1_1nnet1_1_1LengthNormComponent.html#a9d5f6382846c79725a9f78801088542f",
"classkaldi_1_1nnet1_1_1RbmBase.html#a3c5a5bb2d95167e5fc409e94971f0414",
"classkaldi_1_1nnet2_1_1AdditiveNoiseComponent.html#ac58bcd0064a287ce8fec11ae9e10d2fe",
"classkaldi_1_1nnet2_1_1DecodableAmNnet.html#a1a45f1ba36233840e0f42e28703d6ea9",
"classkaldi_1_1nnet2_1_1LogSoftmaxComponent.html#ac58bcd0064a287ce8fec11ae9e10d2fe",
"classkaldi_1_1nnet2_1_1NormalizeComponent.html#a7bc261b04ea91663bea36634558ed779",
"classkaldi_1_1nnet2_1_1TanhComponent.html#a810314e9ffef5bb55807f10654c5d46c",
"classkaldi_1_1nnet3_1_1CompositeComponent.html#a8cbbffc6b7aa97d5e9734b771eb59e75",
"classkaldi_1_1nnet3_1_1DerivativeTimeLimiter.html#ad70a13d2a5ffc3f7e7370f7b4e774a73",
"classkaldi_1_1nnet3_1_1Nnet.html#a7d47c6c3536d985d00cc6dd702c63f72",
"classkaldi_1_1nnet3_1_1OnlineNaturalGradient.html#af12dc036070d7e3229a0232e214c226e",
"classkaldi_1_1nnet3_1_1SumGroupComponent.html#a78b33652566522183152981014dc4e30",
"cmvn-to-nnet_8cc_source.html",
"cu-block-matrix_8cc.html",
"cu-rand_8h.html",
"deterministic-fst-test_8cc.html#a006b00477e4d9250474e76e1ec61bb3f",
"edit-distance-inl_8h.html#a492b0a1d8f894f6bf4781e4a52a6a226",
"feature-plp-test_8cc_source.html",
"fstext-utils-test_8cc.html#a46cc54bb3eb71e64f7d163ab55be9da4",
"globals_func.html",
"gmm-latgen-faster-regtree-fmllr_8cc.html#a0ddf1224851353fc92bfbff6f499fa97",
"group__hmm__group.html#gad94539d80f1ba0b8731c6692b624b7a3",
"group__table__types.html#ga81cb37d43953db92b5eb96473609bcf8",
"io-funcs_8h.html#ga4c7a80f758e878578e78b667f62463a5",
"kaldi-lattice_8h.html#a417e37822095c5adb9680fa07dffea8d",
"kaldi-utils_8h.html#a3508b7804094b45e5dff6d17361106d2",
"lattice-oracle_8cc.html#af32aec9dfd0165361a2f03806191ef9d",
"matrix-dim_8cc.html",
"mel-computations_8h.html",
"namespacemembers_v.html",
"nnet-computation-graph_8cc.html#a0042e072cd4a3244fe595534db8c9392",
"nnet-graph_8h.html#ac4457943f315ab2e900b1f81606404f8",
"nnet-shrink_8cc.html",
"nnet3-am-train-transitions_8cc.html#ad96e7aef845800f1dc88fa2ad1aade28",
"post-to-tacc_8cc_source.html",
"reverse-feats_8cc.html",
"simple-options_8cc.html#a5aff2630938df1898170af3b01f35df0",
"structfst_1_1LatticeDeterminizerPruned_1_1TempArc.html",
"structkaldi_1_1FasterDecoderOptions.html#aeba4456707a8c461884f8207ab387d78",
"structkaldi_1_1LatticeLexiconWordAligner_1_1Tuple.html#a4b8b50ed51288ca2ddbea382a589e02c",
"structkaldi_1_1NBestDecoderOptions.html#aac27eaf00599707440629f2f6a274e02",
"structkaldi_1_1SgmmFmllrConfig.html#a151cccfc9d963f1d28e72d3e34d8178e",
"structkaldi_1_1nnet1_1_1Component.html#a81f78fc173dedefe5a049c0aa3eed2c0aeb908eba323af157dda85b8426fb376c",
"structkaldi_1_1nnet3_1_1CheckComputationOptions.html#ae6464bdbe1cede5eace3852a696187a5",
"structkaldi_1_1nnet3_1_1NnetGenerationOptions.html#aa218ec96ac8161feee41797c780a16f0",
"train-nnet-ensemble_8cc.html#a573bbaf2d11e8ffa24babe6da86a9c89"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';
var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';
var navTreeSubIndices = new Array();

function getData(varName)
{
  var i = varName.lastIndexOf('/');
  var n = i>=0 ? varName.substring(i+1) : varName;
  return eval(n.replace(/\-/g,'_'));
}

function stripPath(uri)
{
  return uri.substring(uri.lastIndexOf('/')+1);
}

function stripPath2(uri)
{
  var i = uri.lastIndexOf('/');
  var s = uri.substring(i+1);
  var m = uri.substring(0,i+1).match(/\/d\w\/d\w\w\/$/);
  return m ? uri.substring(i-6) : s;
}

function localStorageSupported()
{
  try {
    return 'localStorage' in window && window['localStorage'] !== null && window.localStorage.getItem;
  }
  catch(e) {
    return false;
  }
}


function storeLink(link)
{
  if (!$("#nav-sync").hasClass('sync') && localStorageSupported()) {
      window.localStorage.setItem('navpath',link);
  }
}

function deleteLink()
{
  if (localStorageSupported()) {
    window.localStorage.setItem('navpath','');
  } 
}

function cachedLink()
{
  if (localStorageSupported()) {
    return window.localStorage.getItem('navpath');
  } else {
    return '';
  }
}

function getScript(scriptName,func,show)
{
  var head = document.getElementsByTagName("head")[0]; 
  var script = document.createElement('script');
  script.id = scriptName;
  script.type = 'text/javascript';
  script.onload = func; 
  script.src = scriptName+'.js'; 
  if ($.browser.msie && $.browser.version<=8) { 
    // script.onload does not work with older versions of IE
    script.onreadystatechange = function() {
      if (script.readyState=='complete' || script.readyState=='loaded') { 
        func(); if (show) showRoot(); 
      }
    }
  }
  head.appendChild(script); 
}

function createIndent(o,domNode,node,level)
{
  var level=-1;
  var n = node;
  while (n.parentNode) { level++; n=n.parentNode; }
  if (node.childrenData) {
    var imgNode = document.createElement("img");
    imgNode.style.paddingLeft=(16*level).toString()+'px';
    imgNode.width  = 16;
    imgNode.height = 22;
    imgNode.border = 0;
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() {
      if (node.expanded) {
        $(node.getChildrenUL()).slideUp("fast");
        node.plus_img.src = node.relpath+"ftv2pnode.png";
        node.expanded = false;
      } else {
        expandNode(o, node, false, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
    imgNode.src = node.relpath+"ftv2pnode.png";
  } else {
    var span = document.createElement("span");
    span.style.display = 'inline-block';
    span.style.width   = 16*(level+1)+'px';
    span.style.height  = '22px';
    span.innerHTML = '&#160;';
    domNode.appendChild(span);
  } 
}

var animationInProgress = false;

function gotoAnchor(anchor,aname,updateLocation)
{
  var pos, docContent = $('#doc-content');
  if (anchor.parent().attr('class')=='memItemLeft' ||
      anchor.parent().attr('class')=='fieldtype' ||
      anchor.parent().is(':header')) 
  {
    pos = anchor.parent().position().top;
  } else if (anchor.position()) {
    pos = anchor.position().top;
  }
  if (pos) {
    var dist = Math.abs(Math.min(
               pos-docContent.offset().top,
               docContent[0].scrollHeight-
               docContent.height()-docContent.scrollTop()));
    animationInProgress=true;
    docContent.animate({
      scrollTop: pos + docContent.scrollTop() - docContent.offset().top
    },Math.max(50,Math.min(500,dist)),function(){
      if (updateLocation) window.location.href=aname;
      animationInProgress=false;
    });
  }
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  node.expanded = false;
  a.appendChild(node.label);
  if (link) {
    var url;
    if (link.substring(0,1)=='^') {
      url = link.substring(1);
      link = url;
    } else {
      url = node.relpath+link;
    }
    a.className = stripPath(link.replace('#',':'));
    if (link.indexOf('#')!=-1) {
      var aname = '#'+link.split('#')[1];
      var srcPage = stripPath($(location).attr('pathname'));
      var targetPage = stripPath(link.split('#')[0]);
      a.href = srcPage!=targetPage ? url : "javascript:void(0)"; 
      a.onclick = function(){
        storeLink(link);
        if (!$(a).parent().parent().hasClass('selected'))
        {
          $('.item').removeClass('selected');
          $('.item').removeAttr('id');
          $(a).parent().parent().addClass('selected');
          $(a).parent().parent().attr('id','selected');
        }
        var anchor = $(aname);
        gotoAnchor(anchor,aname,true);
      };
    } else {
      a.href = url;
      a.onclick = function() { storeLink(link); }
    }
  } else {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() {
    if (!node.childrenUL) {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  (function (){ // retry until we can scroll to the selected item
    try {
      var navtree=$('#nav-tree');
      navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
    } catch (err) {
      setTimeout(arguments.callee, 0);
    }
  })();
}

function expandNode(o, node, imm, showRoot)
{
  if (node.childrenData && !node.expanded) {
    if (typeof(node.childrenData)==='string') {
      var varName    = node.childrenData;
      getScript(node.relpath+varName,function(){
        node.childrenData = getData(varName);
        expandNode(o, node, imm, showRoot);
      }, showRoot);
    } else {
      if (!node.childrenVisited) {
        getNode(o, node);
      } if (imm || ($.browser.msie && $.browser.version>8)) { 
        // somehow slideDown jumps to the start of tree for IE9 :-(
        $(node.getChildrenUL()).show();
      } else {
        $(node.getChildrenUL()).slideDown("fast");
      }
      if (node.isLast) {
        node.plus_img.src = node.relpath+"ftv2mlastnode.png";
      } else {
        node.plus_img.src = node.relpath+"ftv2mnode.png";
      }
      node.expanded = true;
    }
  }
}

function glowEffect(n,duration)
{
  n.addClass('glow').delay(duration).queue(function(next){
    $(this).removeClass('glow');next();
  });
}

function highlightAnchor()
{
  var aname = $(location).attr('hash');
  var anchor = $(aname);
  if (anchor.parent().attr('class')=='memItemLeft'){
    var rows = $('.memberdecls tr[class$="'+
               window.location.hash.substring(1)+'"]');
    glowEffect(rows.children(),300); // member without details
  } else if (anchor.parents().slice(2).prop('tagName')=='TR') {
    glowEffect(anchor.parents('div.memitem'),1000); // enum value
  } else if (anchor.parent().attr('class')=='fieldtype'){
    glowEffect(anchor.parent().parent(),1000); // struct field
  } else if (anchor.parent().is(":header")) {
    glowEffect(anchor.parent(),1000); // section header
  } else {
    glowEffect(anchor.next(),1000); // normal member
  }
  gotoAnchor(anchor,aname,false);
}

function selectAndHighlight(hash,n)
{
  var a;
  if (hash) {
    var link=stripPath($(location).attr('pathname'))+':'+hash.substring(1);
    a=$('.item a[class$="'+link+'"]');
  }
  if (a && a.length) {
    a.parent().parent().addClass('selected');
    a.parent().parent().attr('id','selected');
    highlightAnchor();
  } else if (n) {
    $(n.itemDiv).addClass('selected');
    $(n.itemDiv).attr('id','selected');
  }
  if ($('#nav-tree-contents .item:first').hasClass('selected')) {
    $('#nav-sync').css('top','30px');
  } else {
    $('#nav-sync').css('top','5px');
  }
  showRoot();
}

function showNode(o, node, index, hash)
{
  if (node && node.childrenData) {
    if (typeof(node.childrenData)==='string') {
      var varName    = node.childrenData;
      getScript(node.relpath+varName,function(){
        node.childrenData = getData(varName);
        showNode(o,node,index,hash);
      },true);
    } else {
      if (!node.childrenVisited) {
        getNode(o, node);
      }
      $(node.getChildrenUL()).css({'display':'block'});
      if (node.isLast) {
        node.plus_img.src = node.relpath+"ftv2mlastnode.png";
      } else {
        node.plus_img.src = node.relpath+"ftv2mnode.png";
      }
      node.expanded = true;
      var n = node.children[o.breadcrumbs[index]];
      if (index+1<o.breadcrumbs.length) {
        showNode(o,n,index+1,hash);
      } else {
        if (typeof(n.childrenData)==='string') {
          var varName = n.childrenData;
          getScript(n.relpath+varName,function(){
            n.childrenData = getData(varName);
            node.expanded=false;
            showNode(o,node,index,hash); // retry with child node expanded
          },true);
        } else {
          var rootBase = stripPath(o.toroot.replace(/\..+$/, ''));
          if (rootBase=="index" || rootBase=="pages" || rootBase=="search") {
            expandNode(o, n, true, true);
          }
          selectAndHighlight(hash,n);
        }
      }
    }
  } else {
    selectAndHighlight(hash);
  }
}

function removeToInsertLater(element) {
  var parentNode = element.parentNode;
  var nextSibling = element.nextSibling;
  parentNode.removeChild(element);
  return function() {
    if (nextSibling) {
      parentNode.insertBefore(element, nextSibling);
    } else {
      parentNode.appendChild(element);
    }
  };
}

function getNode(o, po)
{
  var insertFunction = removeToInsertLater(po.li);
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
      i==l);
  }
  insertFunction();
}

function gotoNode(o,subIndex,root,hash,relpath)
{
  var nti = navTreeSubIndices[subIndex][root+hash];
  o.breadcrumbs = $.extend(true, [], nti ? nti : navTreeSubIndices[subIndex][root]);
  if (!o.breadcrumbs && root!=NAVTREE[0][1]) { // fallback: show index
    navTo(o,NAVTREE[0][1],"",relpath);
    $('.item').removeClass('selected');
    $('.item').removeAttr('id');
  }
  if (o.breadcrumbs) {
    o.breadcrumbs.unshift(0); // add 0 for root node
    showNode(o, o.node, 0, hash);
  }
}

function navTo(o,root,hash,relpath)
{
  var link = cachedLink();
  if (link) {
    var parts = link.split('#');
    root = parts[0];
    if (parts.length>1) hash = '#'+parts[1];
    else hash='';
  }
  if (hash.match(/^#l\d+$/)) {
    var anchor=$('a[name='+hash.substring(1)+']');
    glowEffect(anchor.parent(),1000); // line number
    hash=''; // strip line number anchors
    //root=root.replace(/_source\./,'.'); // source link to doc link
  }
  var url=root+hash;
  var i=-1;
  while (NAVTREEINDEX[i+1]<=url) i++;
  if (i==-1) { i=0; root=NAVTREE[0][1]; } // fallback: show index
  if (navTreeSubIndices[i]) {
    gotoNode(o,i,root,hash,relpath)
  } else {
    getScript(relpath+'navtreeindex'+i,function(){
      navTreeSubIndices[i] = eval('NAVTREEINDEX'+i);
      if (navTreeSubIndices[i]) {
        gotoNode(o,i,root,hash,relpath);
      }
    },true);
  }
}

function showSyncOff(n,relpath)
{
    n.html('<img src="'+relpath+'sync_off.png" title="'+SYNCOFFMSG+'"/>');
}

function showSyncOn(n,relpath)
{
    n.html('<img src="'+relpath+'sync_on.png" title="'+SYNCONMSG+'"/>');
}

function toggleSyncButton(relpath)
{
  var navSync = $('#nav-sync');
  if (navSync.hasClass('sync')) {
    navSync.removeClass('sync');
    showSyncOff(navSync,relpath);
    storeLink(stripPath2($(location).attr('pathname'))+$(location).attr('hash'));
  } else {
    navSync.addClass('sync');
    showSyncOn(navSync,relpath);
    deleteLink();
  }
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;
  o.node.expanded = false;
  o.node.isLast = true;
  o.node.plus_img = document.createElement("img");
  o.node.plus_img.src = relpath+"ftv2pnode.png";
  o.node.plus_img.width = 16;
  o.node.plus_img.height = 22;

  if (localStorageSupported()) {
    var navSync = $('#nav-sync');
    if (cachedLink()) {
      showSyncOff(navSync,relpath);
      navSync.removeClass('sync');
    } else {
      showSyncOn(navSync,relpath);
    }
    navSync.click(function(){ toggleSyncButton(relpath); });
  }

  $(window).load(function(){
    navTo(o,toroot,window.location.hash,relpath);
    showRoot();
  });

  $(window).bind('hashchange', function(){
     if (window.location.hash && window.location.hash.length>1){
       var a;
       if ($(location).attr('hash')){
         var clslink=stripPath($(location).attr('pathname'))+':'+
                               $(location).attr('hash').substring(1);
         a=$('.item a[class$="'+clslink+'"]');
       }
       if (a==null || !$(a).parent().parent().hasClass('selected')){
         $('.item').removeClass('selected');
         $('.item').removeAttr('id');
       }
       var link=stripPath2($(location).attr('pathname'));
       navTo(o,link,$(location).attr('hash'),relpath);
     } else if (!animationInProgress) {
       $('#doc-content').scrollTop(0);
       $('.item').removeClass('selected');
       $('.item').removeAttr('id');
       navTo(o,toroot,window.location.hash,relpath);
     }
  })
}

