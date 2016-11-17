//
// echo_service.hpp
// 
// ActorX auto-generated, do not check in modified versions of this file.
//

#include <actorx/all.hpp>

#include <string>
#include <memory>
#include <utility>


namespace usr
{
class echo_service : public acx::fiber_addon_base
{
public:
  template <class Actor>
  echo_service(Actor&& act)
    : fiber_addon_base(std::forward<Actor>(act))
  {
    auto ptr = shared_from_this();
    act.add_recv_filter(
      acx::atom("EXCEPT"), 
      [ptr](
        acx::actor_id const& from_aid, 
        acx::atom_t type, 
        acx::message& prev_msg, 
        acx::message& src_msg
        ) -> acx::message
      {
        switch (type)
        {
        case acx::atom("EXCEPT"):
          return ptr->filter_recv_except(from_aid, prev_msg, src_msg);
        default:
          return acx::nullmsg;
        }
      });
  }

  virtual ~echo_service()
  {
  }

public:
  void echo(std::string const& e)
  {
    // Post on_echo to background fiber.
    auto& evs = acx::fiber_addon_base::get_ev_service();
    evs.async<acx::fiber_addon_event>(...);
  }

protected:
  void send_echo(std::string const& e)
  {
    send("ECHO", e);
  }

  void send_echo_err(int32_t errcode, std::string const& errmsg)
  {
    send("ECHO_ERR", errcode, errmsg);
  }

  void send_except(std::string const& what)
  {
    send("ECHO", what);
  }

protected:
  virtual void on_echo(std::string const& e) = 0;

  virtual acx::message filter_recv_except(
    acx::actor_id const& from_aid, 
    acx::message& prev_msg,
    acx::message& src_msg
    ) = 0;
};

using echo_service_ptr = std::shared_ptr<echo_service>;

template <class Impl, class Actor>
static echo_service_ptr make_echo_service(Actor&& act)
{
  return std::make_shared<Impl>(std::forward<Actor>(act));
}
}
