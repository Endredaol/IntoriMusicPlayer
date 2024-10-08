#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Windowing;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::IntoriMusicPlayer::implementation
{
	App::App()
	{
		InitializeComponent();
	}

	void App::OnLaunched(winrt::Microsoft::UI::Xaml::LaunchActivatedEventArgs const& e)
	{
		mainwindow_ = make<MainWindow>();

		mainwindow_.ExtendsContentIntoTitleBar(true);

		auto appWindow = mainwindow_.AppWindow();

		auto titleBar = appWindow.TitleBar();

		auto theme = Application::Current().RequestedTheme() == ApplicationTheme::Dark ? ElementTheme::Dark : ElementTheme::Light;
		SetTitleBarTheme(titleBar, theme);

		mainwindow_.Activate();
	}

	HWND App::GetHandleFromWindow(winrt::Microsoft::UI::Xaml::Window const&)
	{
		auto handle{ HWND{} };
		mainwindow_.try_as<IWindowNative>()->get_WindowHandle(&handle);
		return handle;
	}

	double App::GetScaleAdjustment(winrt::Microsoft::UI::Xaml::Window const&)
	{
		auto dpi_x{ ::GetDpiForWindow(GetHandleFromWindow(window)) };
		auto scale_factor_percent{ (dpi_x * 100 + (96 >> 1)) / 96 };
		return scale_factor_percent / 100.;
	}

	void App::AppWindow_Changed(AppWindow sender, AppWindowChangedEventArgs const&) {}

	void App::CustomTitleBar_Loaded(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
	{
		assert(winrt::Microsoft::UI::Windowing::AppWindowTitleBar::IsCustomizationSupported());
		SetDragRegionForCustomTitleBar();
	}

	void App::CustomTitleBar_SizeChanged(Windows::Foundation::IInspectable const&, SizeChangedEventArgs const&)
	{
		assert(winrt::Microsoft::UI::Windowing::AppWindowTitleBar::IsCustomizationSupported());
		assert(mainwindow_.AppWindow().TitleBar().ExtendsContentIntoTitleBar());
		SetDragRegionForCustomTitleBar();
	}

	void App::SetDragRegionForCustomTitleBar()
	{
		assert(winrt::Microsoft::UI::Windowing::AppWindowTitleBar::IsCustomizationSupported());
		auto title_bar{ mainwindow_.AppWindow().TitleBar() };
		assert(title_bar.ExtendsContentIntoTitleBar());
		auto scale_adjustment{ GetScaleAdjustment(mainwindow_) };
		auto app_titlebar{ mainwindow_.Content().try_as<IntoriMusicPlayer::MainWindow>().CustomTitleBar() };
		auto rect{ winrt::Windows::Graphics::RectInt32{} };
		rect.X = static_cast<int32_t>((title_bar.LeftInset() + 32) * scale_adjustment);
		rect.Y = 0;
		rect.Height = static_cast<int32_t>(32 * scale_adjustment);
		rect.Width = static_cast<int32_t>(app_titlebar.ActualWidth() * scale_adjustment - rect.X - title_bar.RightInset());
		title_bar.SetDragRectangles(winrt::array_view(&rect, &rect + 1));
	}

	void App::SetTitleBarTheme(winrt::Microsoft::UI::Windowing::AppWindowTitleBar& titlebar, winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		if (theme == winrt::Microsoft::UI::Xaml::ElementTheme::Dark)
		{
			titlebar.ButtonHoverBackgroundColor(winrt::Microsoft::UI::ColorHelper::FromArgb(255, 45, 45, 45));
			titlebar.ButtonForegroundColor(winrt::Microsoft::UI::Colors::White());
		}
		else if (theme == winrt::Microsoft::UI::Xaml::ElementTheme::Light)
		{
			titlebar.ButtonHoverBackgroundColor(winrt::Microsoft::UI::ColorHelper::FromArgb(255, 233, 233, 233));
			titlebar.ButtonForegroundColor(winrt::Microsoft::UI::Colors::Black());
		}
	}
}
