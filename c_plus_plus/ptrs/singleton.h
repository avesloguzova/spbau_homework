#include <memory>

namespace util
{
    class singleton
    {
        public:
            int field;
            static std::shared_ptr<singleton> get_instance();

            ~singleton()
            {
            }

        private:

        static std::weak_ptr<singleton> p_instance;

        private:

            singleton(){ }
    };
}



