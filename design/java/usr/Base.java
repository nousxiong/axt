
package usr;

import java.nio.channels.AsynchronousSocketChannel;

/**
 * Base
 */
public class Base extends actorx.FreeActor {
	public static Base spawn(actorx.AxSystem axs);

	public actorx.util.Tuple<actorx.ActorId, String> recvReplyFromUtilTest();
	public actorx.util.Tuple<actorx.ActorId, String> recvEchoFromUtilEcho();
	public actorx.MessageGuard recvAny();

	public void sendInitToUtilTest(actorx.ActorId toAid, AsynchronousSocketChannel skt);
	public void sendInitToUtilEcho(actorx.ActorId toAid, int id);
	public void sendEchoToUtilEcho(actorx.ActorId toAid, String e);
	public void sendEndToUtilEcho(actorx.ActorId toAid);
}