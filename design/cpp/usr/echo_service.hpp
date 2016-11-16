//
// echo_service.hpp
// 
// ActorX auto-generated, do not check in modified versions of this file.
//

#include <actorx/all.hpp>

#include <string>


namespace usr
{
class echo_service : public actx::fiber_addon_base
{
public:
  template <class Actor>
  echo_service(Actor act)
    : fiber_addon_base(act)
  {
  }

public:
  void echo(std::string const& e)
  {
    // Post on_echo to background fiber.
    auto& evs = actx::fiber_addon_base::get_ev_service();
    evs.async<actx::fiber_addon_event>(...);
  }

protected:
  virtual void on_echo(std::string const& e) = 0;
};
}
