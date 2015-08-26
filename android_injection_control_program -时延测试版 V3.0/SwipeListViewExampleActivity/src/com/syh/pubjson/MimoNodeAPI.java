package com.syh.pubjson;

/**
 * mimonode APIs for Java Applications.
 *
 * @author mimonode by Biteme.
 * 
 * @version v1.0
 * 
 * @data 2015.6.9
 */

import org.json.*;

import android.util.Log;

import com.github.nkzawa.emitter.*;
import com.github.nkzawa.socketio.client.*;
//import com.github.nkzawa.emitter.Emitter;
import com.github.nkzawa.engineio.client.*;
import com.github.nkzawa.socketio.client.Socket;

public class MimoNodeAPI {

	// private static Socket socket;

	Socket socket = null;

	/**
	 * This function is used to connect the mimonode server.
	 * 
	 * @param callback
	 */
	private void connect(final Callback callback) {
		try {
			// IO.Options opts = new IO.Options();
			// opts.forceNew = true;
			// opts.reconnection = false;
			// opts.reconnectionAttempts = 2;

			// socket = IO.socket("http://10.110.138.196:3006/access", opts);
			socket = IO.socket("http://10.110.138.196:3006/access");
			// socket = IO.socket("http://10.8.56.244:3000/communication");
		} catch (Exception e) {
			e.printStackTrace();
		}
		socket.on(Socket.EVENT_CONNECT, new Emitter.Listener() {
			@Override
			public void call(Object... args) {
				callback.connectCallback();
			}
		});
		socket.on(Socket.EVENT_DISCONNECT, new Emitter.Listener() {
			public void call(Object... args) {
				callback.disconnectCallback();
			}
		});
		socket.on(Socket.EVENT_ERROR, new Emitter.Listener() {
			public void call(Object... args) {
				callback.socketErrorCallback(args[0]);
			}
		});
		socket.connect();
	};

	/**
	 * This function is used to register an account in mimonode.
	 * 
	 * @param userName
	 *            , password, email, callback.
	 * 
	 * @see successCallback,errorCallback,connectCallback,disconnectCallback,
	 *      socketErrorCallback are supposed to Override in this callback.
	 */
	public void register(String userName, String password, String email,
			final Callback callback) {

		this.connect(callback);
		JSONObject userData = new JSONObject();
		try {
			userData.put("userName", userName);
			userData.put("password", password);
			userData.put("email", email);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("register", userData)
				.on("registerSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("registerFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to login mimonode. new messages are accepted from
	 * now on if there are any messages.
	 * 
	 * @param userName
	 *            , password, email, callback.
	 * @throws  
	 * 
	 * @see successCallback, errorCallback, connectCallback, disconnectCallback,
	 *      socketErrorCallback, NewMessageCallback are supposed to Override in
	 *      this callback.
	 */
	public void login(String userId, String password, final Callback callback) {
		this.connect(callback);
		System.out.println("login in mimonodeapi did");
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		socket.on("newMessage", new Emitter.Listener() {
			public void call(Object... args) {
				callback.newMessageCallback((JSONObject) args[0]);
			}
		});
		JSONObject userData = new JSONObject();
		try {
			userData.put("userId", userId);
			userData.put("password", password);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("auth", userData).on("authSucceed", new Emitter.Listener() {
			public void call(Object... args) {
				callback.successCallback((JSONObject) args[0]);
			}
		}).on("authFailed", new Emitter.Listener() {
			public void call(Object... args) {
				callback.errorCallback((JSONObject) args[0]);
			}
		});
	};

	/**
	 * This function is used to logout from mimonode. new messages won't be
	 * accepted until next login succeed.
	 * 
	 * @param
	 */
	public void logout() {
		socket.disconnect();
	}

	/**
	 * This function is used to getStoredMessages from mimonode.
	 * 
	 * @param userId
	 *            , callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void getStoredMessages(String userId, final Callback callback) {
		JSONObject data = new JSONObject();
		try {
			data.put("userId", userId);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("getStoredMessages", data)
				.on("getStoredMessagesSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("getStoredMessagesFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	}

	/**
	 * This function is used to createSpace in mimonode.
	 * 
	 * @param owner
	 *            , spaceName, spaceType, algorithmType, privacy, secureLevel,
	 *            defaultPermission, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void createSpace(String owner, String spaceName, String spaceType,
			String algorithmType, String privacy, String secureLevel,
			String defaultPermission, final Callback callback) {

		JSONObject space = new JSONObject();
		try {
			space.put("spaceName", spaceName);
			space.put("spaceType", spaceType);
			space.put("algorithmType", algorithmType);
			space.put("privacy", privacy);
			space.put("secureLevel", secureLevel);
			space.put("defaultPermission", defaultPermission);
			space.put("owner", owner);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("createSpace", space)
				.on("createSpaceSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("createSpaceFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to createSpace in mimonode.
	 * 
	 * @param owner
	 *            , spaceName, callback,other params are set default value.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void createSpace(String owner, String spaceName,
			final Callback callback) {
		this.createSpace(owner, spaceName, "LevelSpace", "ZeroPointAlgorithm",
				"private", "4", "puber", callback);
	}

	/**
	 * This function is used to deleteSpace in mimonode.
	 * 
	 * @param userId
	 *            , spaceId, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void deleteSpace(String userId, String spaceId,
			final Callback callback) {

		JSONObject space = new JSONObject();
		try {
			space.put("spaceId", spaceId);
			space.put("userId", userId);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("deleteSpace", space)
				.on("deleteSpaceSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("deleteSpaceFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to subscribeOnSpace in mimonode.
	 * 
	 * @param subscriberId
	 *            , spaceId, attrName1, subValue11, attrName2, subValue21,
	 *            subValue22, attrName3, subValue31, subValue32, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void subscribeOnSpace(String subscriberId, String spaceId,
			String attrName1, String subValue11, String subValue12,
			String attrName2, String subValue21, String subValue22,
			String attrName3, String subValue31, String subValue32,
			final Callback callback) {

		JSONObject data = new JSONObject();
		JSONObject subscriber = new JSONObject();
		JSONObject constraint1 = new JSONObject();
		JSONObject constraint2 = new JSONObject();
		JSONObject constraint3 = new JSONObject();
		try {
			constraint1.put("attrName", attrName1);
			constraint1.put("subValue1", subValue11);
			constraint1.put("subValue2", subValue12);
			constraint2.put("attrName", attrName2);
			constraint2.put("subValue1", subValue21);
			constraint2.put("subValue2", subValue22);
			constraint3.put("attrName", attrName3);
			constraint3.put("subValue1", subValue31);
			constraint3.put("subValue2", subValue32);
			JSONObject[] constraints = { constraint1, constraint2, constraint3 };
			subscriber.put("_id", subscriberId);
			subscriber.put("constraints", constraints);
			data.put("subscriber", subscriber);
			data.put("spaceId", spaceId);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("subscribeOnSpace", data)
				.on("subscribeOnSpaceSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("subscribeOnSpaceFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to subscribeOnSpace in mimonode.
	 * 
	 * @param subscriberId
	 *            , spaceId, callback,other params are set default value.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void subscribeOnSpace(String subscriberId, String spaceId,
			final Callback callback) {
		this.subscribeOnSpace(subscriberId, spaceId, "club", "barcerona",
				"bacerona", "player", "messi", "messi", "day", "1", "5",
				callback);
	};

	/**
	 * This function is used to unsubscribeOnSpace in mimonode.
	 * 
	 * @param subscriberId
	 *            , spaceId, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void unsubscribeOnSpace(String subscriberId, String spaceId,
			final Callback callback) {

		JSONObject data = new JSONObject();
		try {
			data.put("spaceId", spaceId);
			data.put("userId", subscriberId);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("unsubscribeOnSpace", data)
				.on("unsubscribeOnSpaceSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("unsubscribeOnSpaceFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to publishOnSpace in mimonode.
	 * 
	 * @param publisherId
	 *            , spaceId, secureLevel, msgType, content, attrName1, value11,
	 *            attrName2, value2, attrName3, value3, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void publishOnSpace(String publisherId, String spaceId,
			String secureLevel, String msgType, String content,
			String attrName1, String value1, String attrName2, String value2,
			String attrName3, String value3, String attrName4, String value4,
			final Callback callback) {

		JSONObject data = new JSONObject();
		JSONObject description1 = new JSONObject();
		JSONObject description2 = new JSONObject();
		JSONObject description3 = new JSONObject();
		JSONObject description4 = new JSONObject();
		try {
			description1.put("attrName", attrName1);
			description1.put("value", value1);
			description2.put("attrName", attrName2);
			description2.put("value", value2);
			description3.put("attrName", attrName3);
			description3.put("value", value3);
			description4.put("attrName", attrName4);
			description4.put("value", value4);
			JSONObject[] descriptions = { description1, description2,
					description3, description4 };
			data.put("spaceId", spaceId);
			data.put("puber", publisherId);
			data.put("secureLevel", secureLevel);
			data.put("msgType", msgType);
			data.put("content", content);
			data.put("descriptions", descriptions);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("publishOnSpace", data)
				.on("publishOnSpaceSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("publishOnSpaceFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to publishOnSpace in mimonode.
	 * 
	 * @param publisherId
	 *            , spaceId, content,callback,other params are set default
	 *            value.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void publishOnSpace(String publisherId, String spaceId,
			String content, final Callback callback) {
		this.publishOnSpace(publisherId, spaceId, "4", "String", content,
				"club", "barcerona", "player", "messi", "day", "3", "day", "3",
				callback);
	};

	/**
	 * This function is used to createThemeOnSpace in mimonode.
	 * 
	 * @param owner
	 *            , spaceId, themeName, themeType, algorithmType, privacy,
	 *            secureLevel, defaultPermission, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void createThemeOnSpace(String owner, String spaceId,
			String themeName, String themeType, String algorithmType,
			String privacy, String secureLevel, String defaultPermission,
			final Callback callback) {

		JSONObject space = new JSONObject();
		JSONObject theme = new JSONObject();
		try {
			theme.put("spaceName", themeName);
			theme.put("spaceType", themeType);
			theme.put("algorithmType", algorithmType);
			theme.put("privacy", privacy);
			theme.put("secureLevel", secureLevel);
			theme.put("defaultPermission", defaultPermission);
			theme.put("owner", owner);
			space.put("spaceId", spaceId);
			space.put("theme", theme);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("createThemeOnSpace", space)
				.on("createThemeOnSpaceSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("createThemeOnSpaceFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to createThemeOnSpace in mimonode.
	 * 
	 * @param owner
	 *            , spaceId , spaceName, callback, other params are set default
	 *            value.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void createThemeOnSpace(String owner, String spaceId,
			String spaceName, final Callback callback) {
		this.createSpace(owner, spaceName, "LevelSpace", "ZeroPointAlgorithm",
				"private", "4", "puber", callback);
	}

	/**
	 * This function is used to deleteThemeOnSpace in mimonode.
	 * 
	 * @param userId
	 *            , spaceId, themeId, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void deleteThemeOnSpace(String userId, String spaceId,
			String themeId, final Callback callback) {

		JSONObject data = new JSONObject();
		try {
			data.put("spaceId", spaceId);
			data.put("themeId", themeId);
			data.put("userId", userId);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("deleteThemeOnSpace", data)
				.on("deleteThemeOnSpaceSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("deleteThemeOnSpaceFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to subscribeOnTheme in mimonode.
	 * 
	 * @param subscriberId
	 *            , spaceId, themeId, attrName1, subValue11, attrName2,
	 *            subValue21, subValue22, attrName3, subValue31, subValue32,
	 *            callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void subscribeOnTheme(String subscriberId, String spaceId,
			String themeId, String attrName1, String subValue11,
			String subValue12, String attrName2, String subValue21,
			String subValue22, String attrName3, String subValue31,
			String subValue32, final Callback callback) {

		JSONObject data = new JSONObject();
		JSONObject subscriber = new JSONObject();
		JSONObject constraint1 = new JSONObject();
		JSONObject constraint2 = new JSONObject();
		JSONObject constraint3 = new JSONObject();
		try {
			constraint1.put("attrName", attrName1);
			constraint1.put("subValue1", subValue11);
			constraint1.put("subValue2", subValue12);
			constraint2.put("attrName", attrName2);
			constraint2.put("subValue1", subValue21);
			constraint2.put("subValue2", subValue22);
			constraint3.put("attrName", attrName3);
			constraint3.put("subValue1", subValue31);
			constraint3.put("subValue2", subValue32);
			// JSONObject[] constraints = { constraint1, constraint2,
			// constraint3 };
			JSONArray constraints = new JSONArray();
			constraints.put(constraint1);
			constraints.put(constraint2);
			constraints.put(constraint3);

			subscriber.put("_id", subscriberId);
			subscriber.put("constraints", constraints);
			data.put("subscriber", subscriber);
			data.put("spaceId", spaceId);
			data.put("themeId", themeId);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("subscribeOnTheme", data)
				.on("subscribeOnThemeSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("subscribeOnThemeFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to subscribeOnTheme in mimonode.
	 * 
	 * @param subscriberId
	 *            , spaceId, callback,other params are set default value.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void subscribeOnTheme(String subscriberId, String spaceId,
			String themeId, final Callback callback) {
		this.subscribeOnTheme(subscriberId, spaceId, themeId, "club",
				"barcerona", "bacerona", "player", "messi", "messi", "day",
				"1", "5", callback);
	};

	/**
	 * This function is used to unsubscribeOnTheme in mimonode.
	 * 
	 * @param subscriberId
	 *            , spaceId, themeId, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void unsubscribeOnTheme(String subscriberId, String spaceId,
			String themeId, final Callback callback) {

		JSONObject data = new JSONObject();
		try {
			data.put("spaceId", spaceId);
			data.put("themeId", themeId);
			data.put("userId", subscriberId);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("unsubscribeOnTheme", data)
				.on("unsubscribeOnThemeSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("unsubscribeOnThemeFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to publishOnTheme in mimonode.
	 * 
	 * @param publisherId
	 *            , spaceId, themeId, secureLevel, msgType, content, attrName1,
	 *            value11, attrName2, value2, attrName3, value3, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void publishOnTheme(String publisherId, String spaceId,
			String themeId, String secureLevel, String msgType, String content,
			String attrName1, String value1, String attrName2, String value2,
			String attrName3, String value3, String attrName4, String value4,
			String attrName5, String value5, String attrName6, String value6,
			String attrName7, String value7, final Callback callback) {
		JSONObject data = new JSONObject();
		JSONObject description1 = new JSONObject();
		JSONObject description2 = new JSONObject();
		JSONObject description3 = new JSONObject();
		JSONObject description4 = new JSONObject();
		JSONObject description5 = new JSONObject();
		JSONObject description6 = new JSONObject();
		JSONObject description7 = new JSONObject();
		try {
			description1.put("attrName", attrName1);
			description1.put("value", value1);
			description2.put("attrName", attrName2);
			description2.put("value", value2);
			description3.put("attrName", attrName3);
			description3.put("value", value3);
			description4.put("attrName", attrName4);
			description4.put("value", value4);
			description5.put("attrName", attrName5);
			description5.put("value", value5);
			description6.put("attrName", attrName6);
			description6.put("value", value6);
			description7.put("attrName", attrName7);
			description7.put("value", value7);
			// JSONObject[] descriptions = {description1,
			// description2,description3, description4};
			// JSONObject descriptions = new JSONObject();
			// descriptions.put("0",description1 );
			JSONArray descriptions = new JSONArray();
			descriptions.put(description1);
			descriptions.put(description2);
			descriptions.put(description3);
			descriptions.put(description4);
			descriptions.put(description5);
			descriptions.put(description6);
			descriptions.put(description7);

			data.put("spaceId", spaceId);
			data.put("themeId", themeId);
			data.put("puber", publisherId);
			data.put("secureLevel", secureLevel);
			data.put("msgType", msgType);
			data.put("content", content);
			data.put("descriptions", descriptions);
			Log.v("description", data.toString());
			// for(int i=0;i<data.get("descriptions").;i++);
			System.out.println("descriptions: " + descriptions.getClass());
			System.out.println("description1: " + descriptions.length());
			System.out.println("data: " + data.getClass());
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("publishOnTheme", data)
				.on("publishOnThemeSucceed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("publishOnThemeFailed", new Emitter.Listener() {
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to publishOnSpace in mimonode.
	 * 
	 * @param publisherId
	 *            , spaceId, themeId, content,callback,other params are set
	 *            default value.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void publishOnTheme(String publisherId, String spaceId,
			String themeId, String content, final Callback callback) {
		this.publishOnTheme(publisherId, spaceId, themeId, "4", "String",
				content, "club", "barcerona", "player", "messi", "day", "3",
				"day", "3", "day", "3", "day", "3", "day", "3", callback);
	};

}