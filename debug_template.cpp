#include <vector>
#include <sstream>

template <class T>
std::ostream& operator<<(std::ostream& out, std::vector<T> vec) {
	out << "[ ";
	for (int i = 0; i < vec.size(); ++i) {
		out << (i ? ", " : "") << vec[i];
	}
	out << " ]";
	return out;
}

#define PRINT_VARS(...) print_vars(#__VA_ARGS__, __VA_ARGS__)
#define PRINT_VARS_DBG(...) if constexpr (OO) PRINT_VARS(__VA_ARGS__)

template <class T, class... Args>
void print_vars(std::vector<std::string> labels, T arg, Args... args) {
	std::string label = labels[labels.size() - sizeof...(args) - 1];
	std::cout << label << " = " << arg;
	if constexpr (sizeof...(args) > 0) {
		std::cout << ",";
		print_vars(labels, args...);
	}
	else {
		std::cout << std::endl;
	}
}

template <class... Args>
void print_vars(std::string labels, Args... args) {
	std::stringstream input_labels(labels);
	std::string label;
	std::vector<std::string> vectorized_lables;
	while (std::getline(input_labels, label, ',')) {
		vectorized_lables.push_back(label);
	}
	print_vars(vectorized_lables, args...);
}