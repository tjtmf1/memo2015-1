package woong.memo;

import android.content.Intent;

import com.google.android.gms.iid.InstanceIDListenerService;

/**
 * Created by WS on 2015. 12. 17..
 */
public class MyInstanceIDListenerService extends InstanceIDListenerService {
    public void onTokenRefresh() {
        Intent intent = new Intent(this, MyGcmRegistrationService.class);
        startService(intent);
    }
}
