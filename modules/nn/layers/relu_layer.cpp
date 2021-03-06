#include "relu_layer.h"
#include <glog/logging.h>

namespace alchemy {

template<typename T>
void ReLuLayer<T>::setup(const vector<Blob<T> *> &input,
                         const vector<Blob<T> *> &output)
{
    LOG(INFO) << "Setting up: " << this->param_.name();
    LOG(INFO) << "input  #0: "  << input[0]->shape();

    output[0]->reshape(input[0]->shape());
    LOG(INFO) << "output #0: "  << output[0]->shape();
}

template<typename T>
void ReLuLayer<T>::ForwardCPU(const vector<Blob<T> *> &input,
                              const vector<Blob<T> *> &output)
{
    auto count = input[0]->count();
    auto input_data = input[0]->data_cptr();
    auto output_data = output[0]->mutable_data_cptr();
    auto alpha = relu_param_.alpha();

    /// max(0, z) + alpha * min(0, z)
    for(auto i = 0; i < count; ++i) {
        output_data[i] = std::max(input_data[i], (T)0.0) + alpha * std::min(input_data[i], (T)0.0);
    }
}

template<typename T>
void ReLuLayer<T>::BackwardCPU(const vector<Blob<T> *> &input,
                               const vector<Blob<T> *> &output)
{
    auto count = input[0]->count();
    auto input_data = input[0]->data_cptr();
    auto input_diff = input[0]->mutable_diff_cptr();
    auto output_diff = output[0]->diff_cptr();
    auto alpha = relu_param_.alpha();

    for(auto i = 0; i < count; ++i) {
        input_diff[i] = output_diff[i] * ((input_data[i] > 0) ? 1 : alpha);
    }
}

template class ReLuLayer<float>;
template class ReLuLayer<double>;
}