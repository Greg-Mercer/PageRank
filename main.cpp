#include "connectivity_matrix.hpp"
#include "helper.hpp"

using namespace std;

int main() {

    vector<bool> ba = helper::read_file();

    Connectivity_Matrix d(ba);

    d.page_rank();

    return 0;
}