#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <vector>
#include <deque>
#include <stack>
#include <utility>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <functional>

#include <iostream>


namespace sol {

	class Solution {
	private:
		using _type = std::int32_t;
		using Point = std::pair<_type, _type>;
		static constexpr auto NOT_MOVE = std::numeric_limits<_type>::max();
		static constexpr auto CAN_MOVE = 0;
        
	private:
		inline static Point string_to_point(const std::string& str) {
			std::stringstream ss(str);
			_type x, y;
			ss >> x >> y;

			return { y,x };
		}

	public:
		Solution() = default;
		~Solution() = default;

		// get the table number 
		inline _type table_number(const Point& point) const {
			return this->_visitsTable[point.second][point.first];
		}

		// set the table number 
		inline void set_table_number(const Point& point, const _type& number) {
			this->_visitsTable[point.second][point.first] = number;
		}

		inline bool in_range(const Point& point) const {
			return (point.first >= 0 && point.first < this->_shape_number)
				&& (point.second >= 0 && point.second < this->_shape_number)
				&& (this->table_number(point) != Solution::NOT_MOVE);
		}

		// lee algorithm
		inline std::stack<Point> lee_algorithm() {
			std::stack<Point> _stk; 
			_stk.push(this->start_point);
			bool find_it = false;

			while (!_stk.empty() && !find_it) {
				std::stack<Point> neighbor_queue; 

				for (; !_stk.empty();  _stk.pop()) {
					auto& now_point = _stk.top();
					auto now_point_val = this->table_number(now_point);

					for (const auto& func : this->FUNCTION_ARR) {
						auto next_point = func(now_point);

						bool condition = !in_range(next_point) 
							|| this->table_number(next_point) 
							|| next_point == this->start_point;

						if (condition) {
							continue;
						}

						this->set_table_number(next_point, now_point_val + 1);
						neighbor_queue.push(next_point);

						find_it = (next_point == this->end_point);

						if (find_it) { break; }
					}

					if (find_it) { break; }
				}

				if (find_it) { break; }

				_stk = neighbor_queue;
			}

			// not find the path 
			if (find_it == false) { 
				return {};
			}

			// find the path from end the start point 
			_stk = {};
			_stk.push(this->end_point);
			this->set_table_number(this->start_point, -1);

			while (_stk.top() != this->start_point) {
				Point now_point = _stk.top(), min_point = _stk.top();
				_type number = this->table_number(now_point);

				for (const auto& func : this->FUNCTION_ARR) {
					auto point = func(now_point);
					bool condition = in_range(point)
						&& this->table_number(point) < number
						&& this->table_number(point) != Solution::CAN_MOVE;

					if (condition) {
						number = this->table_number(point);
						min_point = point;
					}
				}

				_stk.push(min_point);
			}

			return _stk;
		}
		
        inline void read_console(){
			std::string tmp; 
			std::getline(std::cin, tmp);
			this->start_point = Solution::string_to_point(tmp);

			std::getline(std::cin, tmp);
			this->end_point = Solution::string_to_point(tmp);
		
			std::getline(std::cin, tmp);
			this->_shape_number = std::stol(tmp);

			this->_visitsTable.assign(this->_shape_number, std::vector<_type>(this->_shape_number, Solution::NOT_MOVE));

			for (_type y  = 0; y < this->_shape_number ; y++){
				std::cin >> tmp;
				for (int x = 0; x < tmp.size(); x++) {
					if (tmp[x] == '#') {
						continue;
					}
					this->_visitsTable[y][x] = Solution::CAN_MOVE;
				}
			}

		}


		inline std::string run_solution() {
			auto stk = this->lee_algorithm();

			// not find the path 
			if (stk.empty()) {
				return "No path found!";
			}

			// make the path to string
			std::string res = "Shortest Path: Start -> ";
			
			for (; !stk.empty(); stk.pop()) {
				auto& point = stk.top();
				res += "(" + std::to_string(point.second) + ", " + std::to_string(point.first) + ")" + " -> ";
			}

			return res + "End\n";
		}

	public:
		inline static Point up(const Point& point) {
			return { point.first , point.second - 1 };
		}

		inline static Point down(const Point& point) {
			return { point.first , point.second + 1 };
		}

		inline static Point left(const Point& point) {
			return { point.first - 1, point.second };
		}

		inline static Point right(const Point& point) {
			return { point.first + 1, point.second };
		}

	private:
		_type _shape_number;
		bool not_find = false;
		Point start_point, end_point;

		std::vector<std::vector<char>> _maze;
		std::vector<std::vector<_type>> _visitsTable;
		std::vector<std::pair<_type, _type>> _path;

		const std::vector<std::function<Point(const Point&)>> FUNCTION_ARR = {
			Solution::up,
			Solution::down,
			Solution::left,
			Solution::right
		};
	};


}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
    sol::Solution solution; 
	try {
		solution.read_console();

		std::cout << solution.run_solution();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
    return 0; 
}