#include <iostream>
#include <iomanip>
#include "ann/dataloader.h"
#include "ann/dataset.h"
using namespace std;

void data1() {
  xt::xarray<float> data = {1., 2., 3.};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset<float, string> tensor(data, label);

  xt::svector<std::size_t> get_data_shape = tensor.get_data_shape();
  xt::svector<std::size_t> get_label_shape = tensor.get_label_shape();

  stringstream ss;
  ss << "data_shape=[";
  for (size_t i = 0; i < get_data_shape.size(); ++i) {
    ss << get_data_shape[i];
    if (i != get_data_shape.size() - 1) {
      ss << ", ";
    }
  }
  ss << "] label_shape=[";
  for (size_t i = 0; i < get_label_shape.size(); ++i) {
    ss << get_label_shape[i];
    if (i != get_label_shape.size() - 1) {
      ss << ", ";
    }
  }
  ss << "]";

  string output = ss.str();

  cout << "Output:" << output << endl;
}

void data2() {
  xt::xarray<float> data = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset<float, string> tensor(data, label);

  string output = "";
  try {
    DataLabel<float, string> getitem = tensor.getitem(3);
  } catch (const std::out_of_range &e) {
    output = "Error: Out of range exception: " + string(e.what());
  }

  cout << "Output:" << output << endl;
}

void data3() {
  xt::xarray<float> data = {{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  xt::xarray<string> label = {"one", "two", "three"};
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 2, false, true);

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  cout << "Output:" << output.str() << endl;
}

void data4() {
  xt::xarray<float> data = {1, 2, 3, 4};
  xt::xarray<string> label;
  TensorDataset<double, string> ds(data, label);
  DataLoader<double, string> loader(&ds, 3, true, true);

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
 
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }

  cout << "Output:" << output.str() << endl;
}

void data5() {
  xt::xarray<float> data = {1, 2, 3, 4, 5};
  xt::xarray<string>label;
  TensorDataset<float, string> ds(data, label);
  DataLabel<float, string> getitem = ds.getitem(0);
  xt::xarray<float> getData = getitem.getData();
  xt::xarray<string> getLabel = getitem.getLabel();
  DataLoader<float, string> loader(&ds, 2, false, true);

  stringstream output;
  output << "getData=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getData() << " ";
  }
  output << "; getLabel=";
  for (auto it = loader.begin(); it != loader.end(); ++it) {
    output << (*it).getLabel() << " ";
  }
  output << endl;
  output << getData << ";";
  output << getLabel;

  cout << "Output:" << output.str() << endl;
}