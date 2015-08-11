#include <set>
#include <queue>
#include <functional>
#include <glob.h>

template <typename T = size_t, typename Compare = std::less<T>>
struct task_queue
{
    task_queue(const Compare& comp = Compare());
    void push(std::function<void()> function,T priority = T());
    size_t run_one();
    size_t run();
    bool empty() const;
    task_queue(const task_queue& ) = delete;
    task_queue operator = (const task_queue&)=delete ;

private:
    class comparator{
        const Compare comp;
    public:
        const bool operator()( const std::pair<std::function<void()>,T>& lhs, const std::pair<std::function<void()>,T>& rhs ) const{
            return comp(lhs.second,rhs.second);
        }
        comparator(const Compare& comp):
                comp(comp)
        {
        }
    };
    std::priority_queue<std::pair<std::function<void()>,T>, std::vector<std::pair<std::function<void()>,T>>,comparator> queue;
};
template <typename T , typename Compare >
size_t task_queue<T,Compare>::run_one() {
    if(!queue.empty()){
        std::function<void()> function = queue.top().first;
        queue.pop();
        function();
        return 1;
    } else {
        return 0;
    }
}

template <typename T , typename Compare>
size_t task_queue<T,Compare>::run() {
    size_t result = 0;
    while(!queue.empty()){
        run_one();
        ++result;
    }
    return result;
}

template <typename T , typename Compare>
bool task_queue<T,Compare>::empty() const {
    return queue.empty();
}

template <typename T, typename Compare>
task_queue<T,Compare>::task_queue(Compare const& comp)
        : queue(comparator(comp))
{
}

template <typename T, typename Compare>
void task_queue<T,Compare>::push(std::function<void()> function, T priority)
{
    queue.push(std::make_pair(function, priority));
}
