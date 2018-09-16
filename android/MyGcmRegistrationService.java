package woong.memo;

import android.app.IntentService;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.util.Log;

import com.google.android.gms.gcm.GcmPubSub;
import com.google.android.gms.gcm.GoogleCloudMessaging;
import com.google.android.gms.iid.InstanceID;

import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

/**
 * Created by WS on 2015. 12. 17..
 */
public class MyGcmRegistrationService extends IntentService {
    private static final String TAG = "MyRegistrationService";
    private static final String GCM_SENDER_ID = "79539181774";
    private static final String[] TOPICS = {"global"};

    public MyGcmRegistrationService() {
        super(TAG);
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        try {
            synchronized (TAG) {
                InstanceID instanceID = InstanceID.getInstance(this);
                String token = instanceID.getToken(GCM_SENDER_ID,
                        GoogleCloudMessaging.INSTANCE_ID_SCOPE, null);
                sendTokenToServer(token);
                //subscribeTopics(token);

                Log.i(TAG, "GCM Registration Token: " + token);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 이것도
    private void sendTokenToServer(String token) {
        SharedPreferences setting;
        setting = getSharedPreferences("token", 0);
        String temp;
        temp = setting.getString("token", null);

        if (temp != null)
        {
            return;
        }

        SharedPreferences.Editor editor;
        editor = setting.edit();
        editor.putString("token", token);
        editor.apply();

        InsertContent insert = new InsertContent(token);
        insert.execute();


    }

    public class InsertContent extends AsyncTask<Void, Void, Boolean> {

        String mToken;

        InsertContent(String token)
        {
            this.mToken = token;
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            // TODO: attempt authentication against a network service.

            try {
                String urlString = "http://54.201.117.101/memo/insert.php?content=" + mToken;
                URL url = new URL(urlString);
                // +는 금지 단어다.
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();

                connection.setDefaultUseCaches(false);
                connection.setDoInput(true);
                connection.setDoOutput(true);
                connection.setRequestMethod("POST");
                connection.setConnectTimeout(10000);
                connection.setReadTimeout(10000);
                connection.setRequestProperty("Accept", "application/json");
                connection.setRequestProperty("Content-Type", "application/json; charset=UTF-8");
                connection.setRequestProperty("Cache-Control", "no-cache");

                if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                    InputStream is = connection.getInputStream();
                    ByteArrayOutputStream baos = new ByteArrayOutputStream();

                    byte[] byteBuffer = new byte[1024];
                    byte[] byteData = null;
                    int nLength = 0;

                    while ((nLength = is.read(byteBuffer, 0, byteBuffer.length)) != -1)
                        baos.write(byteBuffer, 0, nLength);

                    byteData = baos.toByteArray();

                    String response = new String(byteData);
                    JSONObject responseJSON = new JSONObject(response);
                    int result = Integer.parseInt((String) responseJSON.get("result"));

                    if (result == 1)
                        return true;

                    else
                        return false;

                }
            } catch (Exception e) {
                e.printStackTrace();
                return false;
            }

            return true;
        }

        @Override
        protected void onPostExecute(Boolean success) {
        }
    }

    // 없어도 될듯?
    private void subscribeTopics(String token) throws IOException {
        for (String topic : TOPICS) {
            GcmPubSub pubSub = GcmPubSub.getInstance(this);
            pubSub.subscribe(token, "/topics/" + topic, null);
        }
    }
}
