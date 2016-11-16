
// actor描述模板（Actor Description Template，简称adt)

// 所在包（目录）
package = usr;

// 导入的adata数据结构
adata = gce.adl.actor_id;
adata = gce.adl.match;


// 自由运行的actor
free base
{
  REPLY(string reply) from test;
}

// 运行在用户指定的函数中的actor
fun test
{
  INIT(string what) from base;
}

// 使用回调机制的actor
cb echo
{
  INIT(int32 id) from base, test; // 只有base和test才能给本actor发送
ECHO(string e); // package内的所有actor都能给本actor发送
HELLO(string msg) extern; // 只有package以外的actor才能给本actor发送
END() from base, test;
}

// 生成的cpp代码
// abase_prx.hpp
namespace usr
{
class abase_prx : public actx::actor_prx
{
public:
  abase_prx(actx::as_system& axs, actx::actor_id const& prx_aid)
    : actor_prx(axs, prx_aid)
  {
  }

public:
  void async_reply(std::string const& reply)
  {
    send_reply(from_aid_, reply);
  }

  void async_reply(actx::actor_id const& from_aid, std::string const& reply)
  {
    //axs_.send(sender, prx_aid_, );
  }

  void async_reply(actx::detail::actor_base const& ax, std::string const& reply)
  {
    async_reply(ax.get_actor_id(), reply);
  }
};
}

// atest_prx.hpp
namespace usr
{
class atest_prx : public actx::actor_prx
{
public:
  atest_prx(actx::ax_system& axs, actx::actor_id const& prx_aid)
    : actor_prx(axs, prx_aid)
  {
  }

public:
  //---------------------------------------------------------------------------
  // INIT
  //---------------------------------------------------------------------------
  void async_init(std::string const& what)
  {
    async_init(from_aid_, what);
  }

  void async_init(actx::actor_id const& from_aid, std::string const& what)
  {
    //axs_.send(sender, prx_aid_, );
  }

  void async_init(actx::actor_base const& ax, std::string const& what)
  {
    async_init(ax.get_actor_id(), what);
  }
};
}

// aecho_prx.hpp
namespace usr
{
class aecho_prx : public actx::actor_prx
{
public:
  aecho_prx(actx::ax_system& axs, actx::actor_id const& prx_aid)
    : actor_prx(axs, prx_aid)
  {
  }

public:
  //---------------------------------------------------------------------------
  // INIT
  //---------------------------------------------------------------------------
  void async_init(int32_t const id)
  {
    async_init(from_aid_, id);
  }

  void async_init(actx::actor_id const& from_aid, int32_t const id)
  {
    async_init(from_aid, id);
  }

  void async_init(actx::actor_base const& ax, int32_t const id)
  {
    async_init(ax.get_actor_id(), id);
  }

  //---------------------------------------------------------------------------
  // ECHO
  //---------------------------------------------------------------------------
  void async_echo(std::string const& echo)
  {
    async_echo(from_aid_, echo);
  }

  void async_echo(actx::actor_id const& from_aid, std::string const& echo)
  {
    async_echo(from_aid, echo);
  }

  void async_echo(actx::actor_base const& ax, std::string const& echo)
  {
    async_echo(ax.get_actor_id(), echo);
  }

  //---------------------------------------------------------------------------
  // END
  //---------------------------------------------------------------------------
  void async_end()
  {
    async_end(from_aid_, echo);
  }

  void async_end(actx::actor_id const& from_aid)
  {
    async_end(from_aid);
  }

  void async_end(actx::actor_base const& ax)
  {
    async_end(ax.get_actor_id());
  }
};
}

// abase.hpp
namespace usr
{
class abase : public actx::thread_actor
{
public:
  static abase spawn(actx::ax_system& axs)
  {
    //return abase();
  }

public:
  actx::actor_id recv_reply(std::string& reply)
  {
    auto msg = recv("REPLY");
    reply = msg.get<std::string>();
    return msg.get_sender();
  }

  template <class ActorPrx>
  ActorPrx recv_reply(std::string& reply)
  {
    auto msg = recv("REPLY");
    reply = msg.get<std::string>();
    auto sender = msg.get_sender();
    return ActorPrx(axs_, sender, get_actor_id());
  }

  std::tuple<actx::actor_id, std::string> recv_reply()
  {
    auto msg = recv("REPLY");
    auto reply = msg.get<std::string>();
    return std::make_tuple(msg.get_sender(), reply);
  }
};
}

// atest.hpp
namespace usr
{
class atest : public actx::detail::fiber_actor
{
public:
  template <class F>
  static atest_prx spawn(actx::ax_system& axs, F&& f, fiber_meta meta)
  {
    auto aid = axs.spawn(std::forward<F>(f), meta);
    return atest_prx(axs, aid);
  }

public:
  actx::actor_id recv_init(std::string& what)
  {
    auto msg = recv("INIT");
    what = msg.get<std::string>();
    return msg.get_sender();
  }

  template <class ActorPrx>
  ActorPrx recv_init(std::string& what)
  {
    auto msg = recv("INIT");
    what = msg.get<std::string>();
    auto sender = msg.get_sender();
    return ActorPrx(axs_, sender, get_actor_id());
  }

  std::tuple<actx::actor_id, std::string> recv_init()
  {
    auto msg = recv("INIT");
    auto what = msg.get<std::string>();
    return std::make_tuple(msg.get_sender(), what);
  }
};
}

// aecho.hpp
namespace usr
{
class aecho : public actx::detail::callback_actor
{
public:
  static aecho_prx spawn(actx::ax_system& axs, callback_meta meta)
  {
    auto aid = axs.spawn(meta);
    return aecho_prx(axs, aid);
  }

public:
  void recv_echo()
  {
  }

private:
  void on_start()
  {
  }

  void handle_init(actx::actor_id const& from_aid, std::string const& what)
  {
  }

  void handle_echo(actx::actor_id const& from_aid, std::string const& echo)
  {
  }

  void handle_end(actx::actor_id const& from_aid)
  {
  }

  void on_quit(actx::actor_exit aex)
  {
  }
};
}

// 使用示例代码
int main()
{
  actx::ax_system axs("AXS");

  // Start axs.
  axs.startup();

  // Spawn an thread actor.
  auto base = usr::abase::spawn(axs);

  // Spawn an coroutine based actor and monitor it.
  auto test = usr::atest::spawn(
    axs,
    [logger](usr::atest self)
    {
      std::string what;
      auto base_prx = self.recv_init<usr::abase_prx>(what);
      logger->info("Recv from base: {}", what);

      std::string reply(what.rbegin(), what.rend());

      // Send reply.
      base_prx.async_reply(self, reply);
    },
    actx::fiber_meta()
      .link(actx::link_type::monitored)
      .stack_size(1024 * 256)
      .sync_sire(false)
    );

  test.async_init(base, "Hello World!");

  std::string reply;
  base.recv_reply(reply);
  ACTX_ENSURES(reply == "!dlroW olleH");

  auto aid = base.recv_exit();
  ACTX_ENSURES(aid == test.get_actor_id());

  // Shut axs and wait it quit.
  axs.shutdown();
  logger->info("done.");
}

// 
int main()
{

}