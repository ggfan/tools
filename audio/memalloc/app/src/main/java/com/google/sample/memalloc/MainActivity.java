package com.google.sample.memalloc;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TextView statusText;
    private Switch testSwitch;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        statusText = (TextView)findViewById(R.id.id_status);
        testSwitch = (Switch) findViewById(R.id.id_switch);
        testSwitch.setChecked(false);
        testSwitch.setText("Start Memalloc Test");
        statusText.setText("idle...");
        testSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    if (!startTest()) {
                        return;
                    }
                    testSwitch.setText("Stop Memalloc Test");
                    statusText.setText("testing...");
                    return;
                }
                stopTest();
                testSwitch.setText("Start Memalloc Test");
                statusText.setText("idle...");
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    static {
        System.loadLibrary("mem-alloc");
    }
    public static native boolean  startTest();
    public static native boolean  stopTest();

    public void updateCurStatus(boolean inTesting) {
        statusText.setText(inTesting? "testing..." : "idle...");
    }
}
