#pragma once

#include "App.xaml.g.h"

namespace winrt::IntoriMusicPlayer::implementation
{
	struct App : AppT<App>
	{
		App();

		void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

	private:
		winrt::Microsoft::UI::Xaml::Window window{ nullptr };
		winrt::Microsoft::UI::Xaml::Window window_{ nullptr };

		IntoriMusicPlayer::MainWindow mainwindow_{ nullptr };
		Microsoft::UI::Windowing::AppWindowTitleBar appTitleBar_{ nullptr };

		HWND GetHandleFromWindow(winrt::Microsoft::UI::Xaml::Window const&);
		double GetScaleAdjustment(winrt::Microsoft::UI::Xaml::Window const&);

		void SetDragRegionForCustomTitleBar();
		void CustomTitleBar_Loaded(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
		void AppWindow_Changed(Microsoft::UI::Windowing::AppWindow, Microsoft::UI::Windowing::AppWindowChangedEventArgs const&);
		void CustomTitleBar_SizeChanged(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::SizeChangedEventArgs const&);
		static void SetTitleBarTheme(winrt::Microsoft::UI::Windowing::AppWindowTitleBar& titlebar, winrt::Microsoft::UI::Xaml::ElementTheme theme);
	};
}
