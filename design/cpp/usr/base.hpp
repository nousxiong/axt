//
// base.hpp
// 
// ActorX auto-generated, do not check in modified versions of this file.
//

#include <actorx/all.hpp>

#include <asio.hpp>
#include <tuple>
#include <string>
#include <memory>


namespace usr
{
class base : public actx::free_actor
{
public:
  static base spawn(actx::ax_system& axs);

public:
  // recv REPLY
  actx::actor_id recv_reply_from_util_test(std::string& reply);
  std::tuple<actx::actor_id, std::string> recv_reply_from_util_test();

  // recv ECHO
  actx::actor_id recv_echo_from_util_echo(std::string& e);
  std::tuple<actx::actor_id, std::string> recv_echo_from_util_echo();

  // recv any msg defined (REPLY and ECHO)
  actx::message recv_any();

  void send_init_to_util_test(actx::actor_id const& to_aid, std::shared_ptr<asio::ip::tcp::socket> skt);
  void send_init_to_util_echo(actx::actor_id const& to_aid, int32_t id);
  void send_echo_to_util_echo(actx::actor_id const& to_aid, std::string const& e);
  void send_end_to_util_echo(actx::actor_id const& to_aid);
};
}
