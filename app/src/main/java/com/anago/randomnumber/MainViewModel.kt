package com.anago.randomnumber

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class MainViewModel : ViewModel() {
    private val _randomNumber: MutableLiveData<Int> = MutableLiveData(0)
    val randomNumber: LiveData<Int> = _randomNumber

    fun generateRandomNumber() {
        _randomNumber.value = AppNative.getRandomNumber()
    }
}