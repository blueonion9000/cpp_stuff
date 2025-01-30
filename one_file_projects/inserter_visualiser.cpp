#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string VisualiseIterator(const std::vector<int> &, const std::vector<int>::iterator &);

int main(int argc, char **argv)
{
  int range_l, range_r;
  std::cout << "Enter a range (inclusive): ";
  std::cin >> range_l >> range_r;
  if (range_l > range_r)
    std::swap(range_l, range_r);

  std::vector<int> int_vec(10, 0);
  std::size_t offset = int_vec.size() / 2;
  auto cur_iter = [&]() -> std::vector<int>::iterator { return int_vec.begin() + offset; };
  std::cout << VisualiseIterator(int_vec, cur_iter());
  auto ins = std::inserter(int_vec, cur_iter());
  for (int i = range_l; i <= range_r; ++i) {
    ins = i;  // insert element
    ++offset; // move cursor one element forwards
    std::cout << VisualiseIterator(int_vec, cur_iter());
  }

  return EXIT_SUCCESS;
}

std::string VisualiseIterator(const std::vector<int> &iv, const std::vector<int>::iterator &iter)
{
  std::ostringstream oss_vec, oss_iter;
  bool iter_locked = false;
  for (auto i = iv.begin(); i != iv.end(); ++i) {
    std::ostringstream cur_elem;
    cur_elem << "[" << *i << "]";
    if (not iter_locked) {
      if (i == iter)
        iter_locked = true;
      else
        oss_iter << std::string(cur_elem.str().length(), ' ');
    }
    oss_vec << cur_elem.str();
  }
  oss_vec << "[-]";
  oss_iter << '^';
  return std::string(oss_vec.str() + "\n" + oss_iter.str() + "\n");
}
