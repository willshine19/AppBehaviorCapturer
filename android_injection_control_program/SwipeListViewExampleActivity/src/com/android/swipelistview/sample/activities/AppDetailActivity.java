package com.android.swipelistview.sample.activities;

import com.fortysevendeg.android.swipelistview.R;

import android.app.ActionBar;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.NavUtils;
import android.support.v4.app.TaskStackBuilder;
import android.view.MenuItem;

public class AppDetailActivity extends FragmentActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.another_activity);
		
	
	}

	  @Override
	    public boolean onOptionsItemSelected(MenuItem item) {
	        switch (item.getItemId()) {
	            case android.R.id.home:             
	                Intent upIntent = new Intent(this, SwipeListViewExampleActivity.class);
	                if (NavUtils.shouldUpRecreateTask(this, upIntent)) {                   
	                    TaskStackBuilder.from(this)       
	                            .addNextIntent(upIntent)
	                            .startActivities();
	                    finish();
	                } else {                   
	                    NavUtils.navigateUpTo(this, upIntent);
	                }
	                return true;
	        }
	        return super.onOptionsItemSelected(item);
	    }
	  
	  
	  
	  
	  
	
}
