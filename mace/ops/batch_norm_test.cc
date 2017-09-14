//
// Copyright (c) 2017 XiaoMi All rights reserved.
//

#include "mace/core/operator.h"
#include "mace/ops/ops_test_util.h"

namespace mace {

class BatchNormOpTest : public OpsTestBase {};

TEST_F(BatchNormOpTest, Simple) {
  // Construct graph
  auto& net = test_net();
  OpDefBuilder("BatchNorm", "BatchNormTest")
        .Input("Input")
        .Input("Scale")
        .Input("Offset")
        .Input("Mean")
        .Input("Var")
        .Output("Output")
        .Finalize(net.operator_def());

  // Add input data
  net.AddInputFromArray<float>("Input", {1, 1, 6, 2},
                    {5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15});
  net.AddInputFromArray<float>("Scale", {1}, {4.0f});
  net.AddInputFromArray<float>("Offset", {1}, {2.0});
  net.AddInputFromArray<float>("Mean", {1}, {10});
  net.AddInputFromArray<float>("Var", {1}, {11.67f});

  // Run
  net.RunOp();

  // Check
  Tensor expected = CreateTensor<float>({1, 1, 6, 2},
                                        {-3.86, -3.86, -1.51, -1.51, 0.83, 0.83,
                                         3.17, 3.17, 5.51, 5.51, 7.86, 7.86});

  ExpectTensorNear<float>(expected, *net.GetOutput("Output"), 0.01);
}

}