var dnn3 =
[
    [ "Introduction", "dnn3.html#dnn3_intro", null ],
    [ "Data types in the \"nnet3\" setup.", "dnn3_code_data_types.html", [
      [ "Objectives and background", "dnn3_code_data_types.html#dnn3_dt_problem", null ],
      [ "Outline of approach", "dnn3_code_data_types.html#dnn3_dt_outline", null ],
      [ "Basic data structures in nnet3", "dnn3_code_data_types.html#dnn3_dt_data_structures", [
        [ "Indexes", "dnn3_code_data_types.html#dnn3_dt_datastruct_index", null ],
        [ "Cindexes", "dnn3_code_data_types.html#dnn3_dt_datastruct_cindex", null ],
        [ "ComputationGraph", "dnn3_code_data_types.html#dnn3_dt_datastruct_computation_graph", null ],
        [ "ComputationRequest", "dnn3_code_data_types.html#dnn3_dt_datastruct_computation_request", null ],
        [ "NnetComputation (brief)", "dnn3_code_data_types.html#dnn3_dt_data_struct_computation", null ],
        [ "NnetComputer", "dnn3_code_data_types.html#dnn3_dt_data_struct_computer", null ]
      ] ],
      [ "Neural networks in nnet3", "dnn3_code_data_types.html#dnn3_dt_nnet", [
        [ "Components (the basics)", "dnn3_code_data_types.html#dnn3_dt_nnet_component_basics", null ],
        [ "Components (properties)", "dnn3_code_data_types.html#dnn3_dt_nnet_component_properties", null ],
        [ "Neural network nodes (outline)", "dnn3_code_data_types.html#dnn3_dt_nnet_node_outline", null ],
        [ "Neural network config files", "dnn3_code_data_types.html#dnn3_dt_nnet_config", null ],
        [ "Descriptors in code", "dnn3_code_data_types.html#dnn3_dt_nnet_descriptor_code", null ],
        [ "Neural network nodes (detail)", "dnn3_code_data_types.html#dnn3_dt_nnet_node_detail", null ],
        [ "Neural network (detail)", "dnn3_code_data_types.html#dnn3_dt_nnet_detail", null ]
      ] ],
      [ "NnetComputation (detail)", "dnn3_code_data_types.html#dnn3_dt_nnet_computation", null ]
    ] ],
    [ "Compilation in the \"nnet3\" setup", "dnn3_code_compilation.html", [
      [ "Introduction", "dnn3_code_compilation.html#dnn3_code_compilation_intro", null ],
      [ "Overview of compilation", "dnn3_code_compilation.html#dnn3_compile_overview", null ],
      [ "Creating the computation graph", "dnn3_code_compilation.html#dnn3_compile_graph", [
        [ "Details of ComputationGraph", "dnn3_code_compilation.html#dnn3_compile_graph_graph", null ],
        [ "Building the ComputationGraph", "dnn3_code_compilation.html#dnn3_compile_graph_building", [
          [ "Introduction", "dnn3_code_compilation.html#dnn3_compile_graph_building_intro", null ],
          [ "Basic algorithm", "dnn3_code_compilation.html#dnn3_compile_graph_building_basic", null ],
          [ "Motivation for the algorithm we use", "dnn3_code_compilation.html#dnn3_compile_graph_building_idea", null ],
          [ "The algorithm we use", "dnn3_code_compilation.html#dnn3_compile_graph_building_real", null ],
          [ "Interface of ComputationGraphBuilder", "dnn3_code_compilation.html#dnn3_compile_graph_building_interface", null ]
        ] ]
      ] ],
      [ "Organizing the computation into steps", "dnn3_code_compilation.html#dnn3_compile_steps", [
        [ "Introduction to steps", "dnn3_code_compilation.html#dnn3_compile_steps_intro", null ],
        [ "Creating the sequence of steps (actual algorithm)", "dnn3_code_compilation.html#dnn3_compile_steps_creating", null ]
      ] ],
      [ "Class Compiler", "dnn3_code_compilation.html#dnn3_compile_compiler", [
        [ "Introduction to class Compiler", "dnn3_code_compilation.html#dnn3_compile_compiler_intro", null ],
        [ "Creating the computation", "dnn3_code_compilation.html#dnn3_compile_compiler_creating", null ],
        [ "Setting up the location information", "dnn3_code_compilation.html#dnn3_compile_compiler_location", null ],
        [ "Checking whether derivatives are needed", "dnn3_code_compilation.html#dnn3_compile_compiler_deriv_needed", null ],
        [ "Computing the StepInfo", "dnn3_code_compilation.html#dnn3_compile_compiler_step_info", [
          [ "Allocating matrices and submatrices (background)", "dnn3_code_compilation.html#dnn3_compile_compiler_allocating", null ],
          [ "Allocating matrices and submatrices for StepInfo", "dnn3_code_compilation.html#dnn3_compile_compiler_parts", null ],
          [ "The input locations list", "dnn3_code_compilation.html#dnn3_compile_compiler_locations", null ]
        ] ],
        [ "Computing the input_output_info", "dnn3_code_compilation.html#dnn3_compile_compiler_input_output_info", null ],
        [ "Allocating the matrices", "dnn3_code_compilation.html#dnn3_compile_compiler_allocate", null ],
        [ "The forward computation", "dnn3_code_compilation.html#dnn3_compile_compiler_forward", [
          [ "Forward computation for Components", "dnn3_code_compilation.html#dnn3_compile_compiler_forward_component", null ],
          [ "Forward computation for Descriptors (top-level)", "dnn3_code_compilation.html#dnn3_compile_compiler_forward_descriptor", null ],
          [ "Forward computation for Descriptors (SplitLocations)", "dnn3_code_compilation.html#dnn3_compile_compiler_split_locations", null ],
          [ "Forward computation with DoForwardComputationFromSubmatLocations", "dnn3_code_compilation.html#dnn3_compile_compiler_forward_submat", null ],
          [ "Marking the end of the forward computation", "dnn3_code_compilation.html#dnn3_compile_compiler_forward_end", null ]
        ] ],
        [ "The backward computation", "dnn3_code_compilation.html#dnn3_compile_compiler_backward", null ],
        [ "the matrices  Deallocating the matrices", "dnn3_code_compilation.html#dnn3_compile_compiler_deallocating", null ],
        [ "Adding debug information", "dnn3_code_compilation.html#dnn3_compile_compiler_debug", null ]
      ] ]
    ] ],
    [ "Optimization in the \"nnet3\" setup", "dnn3_code_optimization.html", [
      [ "Introduction", "dnn3_code_optimization.html#dnn3_code_optimization_intro", null ],
      [ "Overview of optimization", "dnn3_code_optimization.html#dnn3_optimize_overview", null ],
      [ "Code analysis", "dnn3_code_optimization.html#dnn3_optimize_analysis", [
        [ "Computation variables", "dnn3_code_optimization.html#dnn3_optimize_analysis_variables", null ],
        [ "Command attributes", "dnn3_code_optimization.html#dnn3_optimize_analysis_attributes", null ],
        [ "Computing the command attributes", "dnn3_code_optimization.html#dnn3_optimize_analysis_attributes_computing", null ],
        [ "Computing the matrix accesses", "dnn3_code_optimization.html#dnn3_optimize_analysis_variable", null ]
      ] ],
      [ "Checking the computation", "dnn3_code_optimization.html#dnn3_optimize_checking", null ],
      [ "Optimization", "dnn3_code_optimization.html#dnn3_optimize_optimization", null ]
    ] ]
];