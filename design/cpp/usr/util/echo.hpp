//
// echo.hpp
// 
// ActorX auto-generated, do not check in modified versions of this file.
//

#include <actorx/all.hpp>

#include <string>
#include <cstdint>


namespace usr
{
namespace util
{
class echo : public actx::callback_actor
{
public:
  template <class CbInit, class CbEcho, class CbHello, class CbEnd>
  static actx::actor_id spawn(
    actx::ax_system& axs,
    actx::callback_meta meta, 
    CbInit&& cb_init,
    CbEcho&& cb_echo,
    CbHello&& cb_hello,
    CbEnd&& cb_end
    );

public:
  // recv INIT
  actx::actor_id recv_init_from_base(int32_t& id);
  std::tuple<actx::actor_id, int32_t> recv_init_from_base();

  actx::actor_id recv_init_from_test(int32_t& id);
  std::tuple<actx::actor_id, int32_t> recv_init_from_test();

  // recv ECHO
  actx::actor_id recv_echo_from_base(std::string& e);
  std::tuple<actx::actor_id, std::string> recv_echo_from_base();

  actx::actor_id recv_echo_from_test(std::string& e);
  std::tuple<actx::actor_id, std::string> recv_echo_from_test();

  actx::actor_id recv_echo_from_echo(std::string& e);
  std::tuple<actx::actor_id, std::string> recv_echo_from_echo();
  
  // send 
};
}
}
