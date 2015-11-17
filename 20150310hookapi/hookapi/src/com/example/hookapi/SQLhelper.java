package com.example.hookapi;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;

public class SQLhelper extends SQLiteOpenHelper{
	public static final String tableName="hero";
	public static final String ID="id";
	public static final String NAME="name";
	public static final String ATT="attack";
	public static final String AGI="agile";
	public static final String INT="intelligence";

	public SQLhelper(Context context, String name, CursorFactory factory,
			int version) {
		super(context, name, factory, version);
	}

	public void onCreate(SQLiteDatabase db){
//		db.execSQL("create table if not exists "+tableName+"("+ID+" integer primary key,"+NAME+" varchar,"
//				+ATT+" integer,"+AGI+" integer,"+INT+" integer)");		
		db.execSQL("create table if not exists hero(id integer primary key,name varchar,attack integer,agile integer,intelligence integer)");		
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		db.execSQL("drop table if exists"+tableName);
		onCreate(db);
	}

}
