import plotly.graph_objects as go
import pandas as pd

"""Plot function to visual raw sensor data"""
variables_dict = {
    'acc_x': 'X axis of Accelerometer', 
    'acc_y': 'Y axis of Accelerometer',
    'acc_z': 'Z axis of Accelerometer', 
    'gyro_x': 'X axis of Gyroscope',
    'gyro_y': 'Y axis of Gyroscope', 
    'gyro_z': 'Z axis of Gyroscope',
    'mag_x': 'X axis of Magnetometer', 
    'mag_y': 'Y axis of Magnetometer',
    'mag_z': 'Z axis of Magnetometer'
    }

# Here \u00B2 mean ^2 and \u03BC micro symbol

units_dict = {
    'acc_x': 'm/s\u00B2', 
    'acc_y': 'm/s\u00B2', 
    'acc_z': 'm/s\u00B2',
    'gyro_x': 'rad/sec', 
    'gyro_y': 'rad/sec', 
    'gyro_z': 'rad/sec',
    'mag_x': '\u03BC T', 
    'mag_y': '\u03BC T', 
    'mag_z': '\u03BC T'}

def update_layout(fig, chart_title: str, **kwargs):
    """Update layout for every chart

    Args:
        fig: A plotly figure
        chart_title (str): A title for chart

    Returns:
        fig: the updated layout for the plotly figure
    """
    # Get kwards data if is needed
    x_title = kwargs.get('xaxis_title', None)
    y_title = kwargs.get('yaxis_title', None)
    height_size = kwargs.get('height', 400)

    # Update layout of the figure
    fig.update_layout(
        title={'text': chart_title, 'x': 0.5},
        legend_title='Driving Event',
        xaxis_title=x_title,
        yaxis_title=y_title,
        template='plotly_white',
        autosize=True,
        height=height_size,
        font=dict(
            family="BlinkMacSystemFont,-apple-system,Segoe UI,Roboto,Oxygen,Ubuntu",
            size=14,
            color="#363636"
        )
    )

    return fig


def line_chart(df, variable):
    """Line chart created with plotly graphic object

    Args:
        df (DataFrame): The dataframe that contains the data to plot
        variable (str): The specific variable to plot

    Returns:
        fig: A plotly figure
    """
    # Create a copy of the data frame to avoid losing important data
    harsh_event_df = df.copy()
    normal_event_df = df.copy()
    x = df['timestamp']
    # Filter column for eventClass
    # Set safe drive events to NaN
    harsh_event_df.loc[df['event_class'] == 0, variable] = None
    # Set harsh drive events to NaN
    normal_event_df.loc[df['event_class'] == 1, variable] = None

    fig = go.Figure()
    fig.add_trace(go.Scatter(
        x=x,
        y=normal_event_df[variable],
        name='Normal Driving',
        marker_color='#64CCC5',
        text=normal_event_df["sr_no"],
        hovertemplate="X = %{x}<br>Y = %{y}<br>SR-NO = %{text}"
    ))
    fig.add_trace(go.Scatter(
        x=x,
        y=harsh_event_df[variable],
        name='Harsh Driving',
        marker_color='#F24C3D',
        text=harsh_event_df["sr_no"],
        hovertemplate="X = %{x}<br>Y = %{y}<br>SR-NO = %{text}"
    ))

    fig = update_layout(fig, f'Plot of {variables_dict[variable]}',
                        xaxis_title='Event Time', yaxis_title=units_dict[variable])
    fig.update_yaxes(nticks=12)
    fig.update_xaxes(nticks=12, tickangle=45)

    return fig

# Loading raw sensor data
df = pd.read_csv("./Raw data/paved_sudden-acc_const-acc-at-20kmph_22-3-2023_19-3-37.csv")

# selecting required variables from dataset to plot
variables = ['acc_x','acc_y','acc_z','gyro_x','gyro_y','gyro_z','mag_x','mag_y',
             'mag_z']

for var in variables:
    fig = line_chart(df, var)
    fig.show()