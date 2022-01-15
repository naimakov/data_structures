#include <assert.h>

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;

time_t t_start, t_end;

/**
 * Network packet processing simulation
 * Implement a program to simulate the processing of network packets.
 * Input:
 *      int S, n - the size of buffer and number of packets
 *      ...
 *      A_i, P_i - the time of arrival and the processing time
 *      ...
 * Output:
 *      -1 if ith packet was dropped or
 *      int start_time -  start time of ith packet processing
 * Constraints:
 *      1 <= S <= 10^5, 0 <= n <= 10^5,
 *      0 <= A_i <= 10^6, 0 <= P_i <= 10^3,
 *      A_i <= A_i+1 for 1 <= i <= n - 1
 * Time limit: 2 sec
 * Memory limit: 512 mb
 */
void tic(int mode = 0) {
  if (mode == 0)
    t_start = time(0);
  else {
    t_end = time(0);
    cout << "Elapsed time is " << difftime(t_end, t_start) << " seconds\n";
  }
}
void toc() { tic(1); }

struct Request {
  Request(int arrival_time, int process_time)
      : arrival_time(arrival_time), process_time(process_time) {}

  int arrival_time;
  int process_time;
};

struct Response {
  Response(bool dropped, int start_time)
      : dropped(dropped), start_time(start_time) {}

  bool dropped;
  int start_time;
};

class Buffer {
 public:
  Buffer(int size) : size_(size), finish_time_() {}

  Response Process(const Request &request) {
    // if first, calculate the finish time and return arrival time
    if (finish_time_.empty()) {
      finish_time_.push(request.arrival_time + request.process_time);
      return Response(0, request.arrival_time);
    } else {
      // remove all packets processed before current one
      while (!finish_time_.empty() &&
             finish_time_.front() <= request.arrival_time) {
        finish_time_.pop();
      }
      // if buffer is empty, calculate the finish time and return arrival time
      if (finish_time_.empty()) {
        finish_time_.push(request.arrival_time + request.process_time);
        return Response(0, request.arrival_time);
      }
      // if buffer is not full, finish time = finish time of last packet +
      // processing time of current packet
      if (finish_time_.size() < size_) {
        int start_time = finish_time_.back();
        finish_time_.push(start_time + request.process_time);
        return Response(0, start_time);
      } else {
        // if buffer is full, mark the current packet as dropped
        return Response(1, 0);
      }
    }
  }

 private:
  int size_;
  std::queue<int> finish_time_;
};

std::vector<Request> ReadRequests() {
  std::vector<Request> requests;
  int count;
  std::cin >> count;
  for (int i = 0; i < count; ++i) {
    int arrival_time, process_time;
    std::cin >> arrival_time >> process_time;
    requests.push_back(Request(arrival_time, process_time));
  }
  return requests;
}

std::vector<Response> ProcessRequests(const std::vector<Request> &requests,
                                      Buffer *buffer) {
  std::vector<Response> responses;
  for (int i = 0; i < requests.size(); ++i)
    responses.push_back(buffer->Process(requests[i]));
  return responses;
}

void PrintResponses(const std::vector<Response> &responses) {
  for (int i = 0; i < responses.size(); ++i)
    std::cout << (responses[i].dropped ? -1 : responses[i].start_time)
              << std::endl;
}

int main() {
  int size;
  std::cin >> size;
  std::vector<Request> requests = ReadRequests();

  Buffer buffer(size);
  std::vector<Response> responses = ProcessRequests(requests, &buffer);

  PrintResponses(responses);
  return 0;
}
