function segment = simpleSegment(data,num_segments,forceplot)

% The basic algorithm works by creating a fine segmented representation then merging the lowest cost segments until only 'num_segments' remain.

left_x       = [1 : 2 : size(data,1)-1];    % Find the left x values vector for the "fine segmented representation".
right_x      = left_x + 1;                  % Find the right x values vector for the "fine segmented representation".
right_x(end) = size(data,1);                % Special case, the rightmost endpoint.
number_of_segments = length(left_x );       % Calculate the number of segments in the initial "fine segmented representation".

data = (data - mean(data));
data = data ./ std(data);

segment = [];
% if nargin > 2
%     figure;
%     plot(data);
% end

% Initialize the segments in the "fine segmented representation". 

for i = 1 : number_of_segments 
   
   segment(i).lx = left_x(i);
   segment(i).rx = right_x(i);
   segment(i).mc = inf;
end;

% Initialize the merge cost of the segments in the "fine segmented representation". 

for i = 1 : number_of_segments - 1
   %coef = polyfit([segment(i).lx :segment(i+1).rx]',data(segment(i).lx :segment(i+1).rx),1);
   %best = (coef(1)*( [segment(i).lx :segment(i+1).rx]' ))+coef(2);
   step = (data(segment(i + 1).rx) - data(segment(i).lx)) / (segment(i + 1).rx - segment(i).lx);
   best = [data(segment(i).lx):step:data(segment(i + 1).rx)]';
   segment(i).mc = sum((data([segment(i).lx :segment(i+1).rx]')-best).^2);
end;

% Keep merging the lowest cost segments until only 'num_segments' remain. 

errRecon = 0;

while errRecon < 0.05
   
   
   [value, i ] = min([segment(:).mc]);                              % Find the location "i", of the cheapest merge.      
   
   if i > 1 & i < length(segment) -1								% The typical case, neither of the two segments to be merged are end segments
      
    	%coef = polyfit([segment(i).lx :segment(i+2).rx]',data(segment(i).lx :segment(i+2).rx),1);
    	%best = (coef(1)*( [segment(i).lx :segment(i+2).rx]' ))+coef(2);
       
        step = (data(segment(i + 2).rx) - data(segment(i).lx)) / (segment(i + 2).rx - segment(i).lx);
        best = [data(segment(i).lx):step:data(segment(i + 2).rx)]';
        segment(i).mc = sum((data([segment(i).lx :segment(i+2).rx]')-best).^2);

	 	segment(i).rx = segment(i+1).rx;
    	segment(i+1) = [];
    
    	i = i - 1;
    
        %coef = polyfit([segment(i).lx :segment(i+1).rx]',data(segment(i).lx :segment(i+1).rx),1);
    	%best = (coef(1)*( [segment(i).lx :segment(i+1).rx]' ))+coef(2);
    
        step = (data(segment(i + 1).rx) - data(segment(i).lx)) / (segment(i + 1).rx - segment(i).lx);
        best = [data(segment(i).lx):step:data(segment(i + 1).rx)]';
        segment(i).mc = sum((data([segment(i).lx :segment(i+1).rx]')-best).^2);
       
   elseif i == 1                                                    % Special case: The leftmost segment must be merged.
       
	    %coef = polyfit([segment(i).lx :segment(i+2).rx]',data(segment(i).lx :segment(i+2).rx),1);
    	%best = (coef(1)*( [segment(i).lx :segment(i+2).rx]' ))+coef(2);
        step = (data(segment(i + 2).rx) - data(segment(i).lx)) / (segment(i + 2).rx - segment(i).lx);
        best = [data(segment(i).lx):step:data(segment(i + 2).rx)]';
    	segment(i).mc = sum((data([segment(i).lx :segment(i+2).rx]')-best).^2);

	 	segment(i).rx = segment(i+1).rx;
        segment(i+1) = [];
              
   else                                                             % Special case: The rightmost segment must be merged.
     
       segment(i).rx = segment(i+1).rx;
       segment(i).mc = inf;
       segment(i+1) = [];
    
       i = i - 1;
       
       %coef = polyfit([segment(i).lx :segment(i+1).rx]',data(segment(i).lx :segment(i+1).rx),1);
       %best = (coef(1)*( [segment(i).lx :segment(i+1).rx]' ))+coef(2);
    
       step = (data(segment(i + 1).rx) - data(segment(i).lx)) / (segment(i + 1).rx - segment(i).lx);
       best = [data(segment(i).lx):step:data(segment(i + 1).rx)]';
       segment(i).mc = sum((data([segment(i).lx :segment(i+1).rx]')-best).^2);

   end;
   
   errRecon = reconstructError(segment, data)
           
end;


%----------------------------------------------
residuals=[];

for i = 1 : length(segment) 
   
        %coef = polyfit([segment(i).lx :segment(i).rx]',data(segment(i).lx :segment(i).rx),1);
    	%best = (coef(1)*( [segment(i).lx :segment(i).rx]' ))+coef(2);
        
        step = (data(segment(i).rx) - data(segment(i).lx)) / (segment(i).rx - segment(i).lx);
        best = [data(segment(i).lx):step:data(segment(i).rx)]';
        residuals = [ residuals ; sum((data([segment(i).lx :segment(i).rx]')-best).^2)];
end;




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% If the user passed in an extra argument, then plot the original time series, together with the segments %%%%%%%%%%%%%


if nargin > 2
    figure;
    hold on;
    plot(data,'r'); 
end; 

   
    temp = [];
    for i = 1 : length(segment) 
   
      %coef = polyfit([segment(i).lx :segment(i).rx]',data(segment(i).lx :segment(i).rx),1);
      %best = (coef(1)*( [segment(i).lx :segment(i).rx]' ))+coef(2);
      
      step = (data(segment(i).rx) - data(segment(i).lx)) / (segment(i).rx - segment(i).lx);
      best = [data(segment(i).lx):step:data(segment(i).rx)]';
      segment(i).ly = best(1);
      segment(i).ry = best(end);
      segment(i).mc = residuals(i);
      
      if nargin > 2
            plot([segment(i).lx:segment(i).rx]', best,'b');
      end;
  
      temp = [temp; [segment(i).ly segment(i).ry]];
   
    end;

    
if nargin > 2
    for i = 1 : length(segment)  - 1 
        plot([segment(i).rx :segment(i+1).lx]', [ temp(i,2) temp(i+1,1)  ],'g');
    end;
end;

function error = reconstructError(segments, data)
    segReconstructed = zeros(length(data), 1);
    for i = 1:length(segments)
        tmpSegment = resample([data(segments(i).lx) data(segments(i).rx)], (segments(i).rx - segments(i).lx) + 1, 2);
        segReconstructed(segments(i).lx:segments(i).rx) = tmpSegment;
    end
    segReconstructed
    error = sqrt(sum((data - segReconstructed) .^ 2)) ./ length(data);